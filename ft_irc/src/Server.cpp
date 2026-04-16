#include "Server.hpp"

#include <algorithm>
#include <cstring>
#include <cerrno>
#include <csignal>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

static void setNonBlocking(int fd) {
    int fl = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

Server::Server(int port, const std::string &password)
: _port(port), _password(password), _listenfd(-1) {
    std::signal(SIGPIPE, SIG_IGN);
    setupSocket();
}

Server::~Server() {
    if (_listenfd >= 0) close(_listenfd);
}

void Server::setupSocket()
{
    _listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_listenfd < 0) throw std::runtime_error("socket failed");

    int yes = 1;
    setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    setNonBlocking(_listenfd);

    sockaddr_in a; std::memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_ANY);
    a.sin_port = htons(_port);

    if (::bind(_listenfd, (sockaddr*)&a, sizeof(a)) < 0)
        throw std::runtime_error("bind failed");
    if (::listen(_listenfd, 128) < 0)
        throw std::runtime_error("listen failed");

    _pfds.clear();
    struct pollfd p; p.fd = _listenfd; p.events = POLLIN; p.revents = 0;
    _pfds.push_back(p);
}

void Server::addPollFd(int fd, short events) {
    struct pollfd p; p.fd = fd; p.events = events; p.revents = 0;
    _pfds.push_back(p);
}

void Server::removePollFd(int fd) {
    for (std::vector<struct pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); ++it) {
        if (it->fd == fd) { _pfds.erase(it); break; }
    }
}

void Server::run()
{
    while (true)
    {
        int pr = ::poll(&_pfds[0], _pfds.size(), 1000);
        if (pr < 0) continue;

        std::size_t n = _pfds.size();
        std::vector< std::pair<int,std::string> > toClose;

        for (std::size_t i = 0; i < n; ++i)
        {
            int fd = _pfds[i].fd;
            short re = _pfds[i].revents;
            if (!re) continue;

            if (fd == _listenfd)
            {
                if (re & POLLIN)
                {
                    for (;;)
                    {
                        int cfd = ::accept(_listenfd, 0, 0);
                        if (cfd < 0)
                        {
                            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                break;
                            } else {
                                std::cerr << "Warning: accept failed with error: " << strerror(errno) << std::endl;
                                break;
                            }
                        }
                        setNonBlocking(cfd);
                        addPollFd(cfd, POLLIN);
                        Client c; c.fd = cfd;
                        _clients[cfd] = c;
                    }
                }
            }
            else
            {
                if (re & POLLIN)
                {
                    char buf[1024];
                    ssize_t r = ::recv(fd, buf, sizeof(buf), 0);
                    if (r <= 0) {
                        toClose.push_back(std::make_pair(fd, r==0?"eof":"recvfail"));
                    } else {
                        Client &cl = _clients[fd];
                        cl.recvbuf.append(buf, r);

                        for (;;)
                        {
                            std::string::size_type pcrlf = cl.recvbuf.find("\r\n");
                            std::string::size_type plf   = cl.recvbuf.find('\n');
                            std::string::size_type p;
                            if (pcrlf != std::string::npos && plf != std::string::npos)
                                p = (pcrlf < plf ? pcrlf : plf);
                            else
                                p = (pcrlf != std::string::npos ? pcrlf : plf);
                            if (p == std::string::npos) break;

                            std::string line = cl.recvbuf.substr(0, p);
                            if (pcrlf != std::string::npos && p == pcrlf)
                                cl.recvbuf.erase(0, p + 2);
                            else
                                cl.recvbuf.erase(0, p + 1);

                            if (line.size() > 512) line.erase(512);

                            IRCMessage m;
                            if (!parseIRCLine(line, m)) continue;
                            handleMessage(fd, m);
                        }
                    }
                }
                if (re & POLLOUT) {
                    if (_clients.find(fd) != _clients.end()) {
                        Client &cl = _clients[fd];
                        if (!cl.sendbuf.empty()) {
                            ssize_t ns = ::send(fd, cl.sendbuf.data(),
                                                cl.sendbuf.size(), MSG_NOSIGNAL);
                            if (ns > 0) cl.sendbuf.erase(0, ns);
                            if (ns < 0 && errno!=EAGAIN && errno!=EWOULDBLOCK)
                                toClose.push_back(std::make_pair(fd, "sendfail"));
                        }
                        if (_clients.find(fd) != _clients.end() && cl.sendbuf.empty())
                        {
                            if (cl.should_close) {
                                toClose.push_back(std::make_pair(fd, "closed_by_server"));
                            } else {
                                for (std::size_t k = 0; k < _pfds.size(); ++k)
                                    if (_pfds[k].fd == fd) { _pfds[k].events &= ~POLLOUT; break; }
                            }
                        }
                    }
                }
                if (re & (POLLERR|POLLHUP)) {
                    toClose.push_back(std::make_pair(fd, (re&POLLERR)?"pollerr":"pollhup"));
                }
            }
            _pfds[i].revents = 0;
        }

        for (std::size_t t = 0; t < toClose.size(); ++t) {
            disconnect(toClose[t].first, toClose[t].second);
        }
        if (!toClose.empty()) {
            continue;
        }
    }
}

void Server::disconnect(int fd, const std::string &why)
{
    std::map<int, Client>::iterator itc = _clients.find(fd);
    if (itc != _clients.end()) {
        Client &c = itc->second;

        if (!c.nick.empty()) {
            for (std::map<std::string, std::set<int> >::iterator it = _chans.begin();
                 it != _chans.end(); ++it) {
                if (it->second.count(fd)) {
                    std::string msg = ":" + c.nick + " QUIT :" + why + "\r\n";
                    broadcastToChannel(it->first, msg, fd);
                    it->second.erase(fd);

                    if (_chanOps[it->first].count(fd))
                    {
                        _chanOps[it->first].erase(fd);
                        if (!it->second.empty())
                        {
                            int new_op = *(it->second.begin());
                            _chanOps[it->first].insert(new_op);
                            std::string newNick = _clients[new_op].nick;
                            std::string opMsg = ":ircserv MODE " + it->first + " +o " + newNick + "\r\n";
                            queueSend(new_op, opMsg);
                            broadcastToChannel(it->first, opMsg, new_op);
                        }
                    }

                    _chanInvited[it->first].erase(fd);
                }
            }
        }
        _clients.erase(itc);
    }

    for (std::map<std::string, std::set<int> >::iterator it = _chans.begin(); it != _chans.end(); ) {
        if (it->second.empty()) {
            _chanOps.erase(it->first);
            _chanInvited.erase(it->first);
            _chans.erase(it++);
        } else {
            ++it;
        }
    }

    removePollFd(fd);
    ::close(fd);
}

void Server::queueSend(int fd, const std::string &data)
{
    std::map<int, Client>::iterator it = _clients.find(fd);
    if (it == _clients.end()) return;
    it->second.sendbuf += data;
    for (std::size_t i = 0; i < _pfds.size(); ++i)
        if (_pfds[i].fd == fd) { _pfds[i].events |= POLLOUT; break; }
}

void Server::sendNumeric(int fd, const std::string &code,
                         const std::string &args,
                         const std::string &text)
{
    std::map<int, Client>::iterator it = _clients.find(fd);
    if (it == _clients.end()) return;

    const Client &c = it->second;
    std::string nick = c.nick.empty() ? "*" : c.nick;

    std::string line = ":ircserv " + code + " " + nick;
    if (!args.empty()) line += " " + args;
    if (!text.empty()) line += " :" + text;
    line += "\r\n";
    queueSend(fd, line);

    std::string human = ":ircserv NOTICE " + nick + " :[" + code + "]";
    if (!args.empty()) human += " " + args;
    if (!text.empty()) human += " — " + text;
    human += "\r\n";
    queueSend(fd, human);
}



bool Server::nickInUse(const std::string &nick) const {
    for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
        if (it->second.nick == nick) return true;
    return false;
}

int Server::findFdByNick(const std::string &nick) const {
    for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
        if (it->second.nick == nick) return it->first;
    return -1;
}

bool Server::isChanMember(const std::string &ch, int fd) const {
    std::map<std::string, std::set<int> >::const_iterator it = _chans.find(ch);
    return (it != _chans.end() && it->second.count(fd) != 0);
}

bool Server::isChanOp(const std::string &ch, int fd) const {
    std::map<std::string, std::set<int> >::const_iterator it = _chanOps.find(ch);
    return (it != _chanOps.end() && it->second.count(fd) != 0);
}

void Server::tryRegister(Client &c)
{
    if (c.registered) return;
    bool passok = (_password.empty() || c.pass_ok);
    if (passok && !c.nick.empty() && !c.user.empty())
    {
        c.registered = true;
        queueSend(c.fd, ":ircserv 001 " + c.nick + " :Welcome to ft_irc, " + c.nick + "\r\n");
        queueSend(c.fd, ":ircserv 002 " + c.nick + " :Your host is ircserv\r\n");
        queueSend(c.fd, ":ircserv 003 " + c.nick + " :This server was created now\r\n");
        queueSend(c.fd, ":ircserv 004 " + c.nick + " ircserv 0 0\r\n");
    }
}

void Server::broadcastToChannel(const std::string &chan,
                                const std::string &line,
                                int except_fd)
{
    std::map<std::string, std::set<int> >::iterator itc = _chans.find(chan);
    if (itc == _chans.end()) return;
    std::set<int> &s = itc->second;
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
        if (*it == except_fd) continue;
        if (_clients.find(*it) != _clients.end()) queueSend(*it, line);
    }
}

void Server::handleMessage(int fd, const IRCMessage &m)
{
    Client &c = _clients[fd];

    if (m.command == "CAP") {
        return;
    }

    if (m.command == "PASS")
    {
        if (m.params.empty() && m.trailing.empty()) {
            sendNumeric(fd, "461", "PASS", "Not enough parameters"); 
            return; 
        }
        if (c.registered) { sendNumeric(fd, "462", "PASS", "You may not reregister"); return; }
        
        std::string pw;
        if (!m.params.empty()) pw = m.params[0];
        else if (!m.trailing.empty()) pw = m.trailing;

        if (_password.empty() || pw == _password) {
            c.pass_ok = true;
        } else {
            sendNumeric(fd, "464", "", "Password incorrect");
            c.should_close = true;
            return;
        }
        tryRegister(c);
        return;
    }

    if (m.command == "NICK")
    {
        if (m.params.empty()) {
            sendNumeric(fd, "431", "", "No nickname given");
            return;
        }

        std::string n = m.params[0];

        int existingFd = findFdByNick(n);
        if (existingFd != -1 && existingFd != fd) {
            sendNumeric(fd, "433", n, "Nickname is already in use");
            return;
        }

        if (c.nick == n)
            return;

        std::string old = c.nick;
        c.nick = n;
        tryRegister(c);

        if (!old.empty() && old != n) {
            std::string nickMsg = ":" + old + " NICK :" + n + "\r\n";
            queueSend(fd, nickMsg);
            for (std::map<std::string, std::set<int> >::iterator it = _chans.begin(); it != _chans.end(); ++it) {
                if (it->second.count(fd)) broadcastToChannel(it->first, nickMsg, fd);
            }
        }
        return;
    }

    if (m.command == "USER")
    {
        if (c.registered) { sendNumeric(fd, "462", "USER", "You may not reregister"); return; }
        if (m.params.size() < 1) { sendNumeric(fd, "461", "USER", "Not enough parameters"); return; }
        c.user = m.params[0];
        if (!m.trailing.empty()) c.realname = m.trailing;
        tryRegister(c); return;
    }

    if (m.command == "PING")
    {
        std::string token = m.trailing.empty() ? (m.params.empty() ? "" : m.params[0]) : m.trailing;
        std::string pong = ":ircserv PONG :" + token + "\r\n";
        queueSend(fd, pong);
        return;
    }

    if (!c.registered
        && m.command != "PASS" && m.command != "NICK" && m.command != "USER"
        && m.command != "PING" && m.command != "CAP" && m.command != "QUIT")
    {
        std::string why = "You have not registered";
        if (!_password.empty() && !c.pass_ok)      why += " (need PASS)";
        else if (c.nick.empty())                   why += " (need NICK)";
        else if (c.user.empty())                   why += " (need USER)";
        sendNumeric(fd, "451", "", why);
        return;
    }

    if (m.command == "JOIN")
    {
        if (m.params.empty()) { sendNumeric(fd, "461", "JOIN", "Not enough parameters"); return; }
        std::string ch = m.params[0];
        if (ch.empty() || ch[0] != '#') { sendNumeric(fd, "479", ch, "Illegal channel name"); return; }
        std::string providedKey = (m.params.size() >= 2 ? m.params[1] : "");

        if (isChanMember(ch, fd))
            return;

        bool created = (_chans.find(ch) == _chans.end());

        if (_chanInviteOnly[ch] && _chanInvited[ch].count(fd) == 0) {
            sendNumeric(fd, "473", ch, "Cannot join channel (+i)");
            return;
        }
        if (_chanLimit.find(ch) != _chanLimit.end()) {
            int lim = _chanLimit[ch];
            std::size_t cur = _chans[ch].size();
            if (lim > 0 && cur >= static_cast<std::size_t>(lim)) {
                sendNumeric(fd, "471", ch, "Channel is full");
                return;
            }
        }
        if (_chanKey.find(ch) != _chanKey.end()) {
            if (_chanKey[ch] != providedKey) {
                sendNumeric(fd, "475", ch, "Bad channel key");
                return;
            }
        }

        _chans[ch].insert(fd);
        if (created) {
            _chanOps[ch].insert(fd);
            if (_chanTopicLock.find(ch) == _chanTopicLock.end()) _chanTopicLock[ch] = false;
            if (_chanInviteOnly.find(ch) == _chanInviteOnly.end()) _chanInviteOnly[ch] = false;
        }
        _chanInvited[ch].erase(fd);

        std::string joinMsg = ":" + c.nick + " JOIN " + ch + "\r\n";
        broadcastToChannel(ch, joinMsg, -1);

        std::map<std::string, TopicInfo>::const_iterator tp = _topics.find(ch);
        if (tp != _topics.end() && !tp->second.text.empty()) {
            queueSend(fd, ":ircserv 332 " + c.nick + " " + ch + " :" + tp->second.text + "\r\n");
            std::ostringstream wh;
            wh << ":ircserv 333 " << c.nick << " " << ch << " " << tp->second.setter << " " << tp->second.setat << "\r\n";
            queueSend(fd, wh.str());
        } else {
            sendNumeric(fd, "331", ch, "No topic is set");
        }

        std::string names;
        const std::set<int> &members = _chans[ch];
        for (std::set<int>::const_iterator it = members.begin(); it != members.end(); ++it)
        {
            std::map<int, Client>::const_iterator ci = _clients.find(*it);
                if (ci != _clients.end() && !ci->second.nick.empty())
                {
                    if (!names.empty()) names += " ";
                    if (isChanOp(ch, *it)) names += "@";
                    names += ci->second.nick;
                }
        }
        queueSend(fd, ":ircserv 353 " + c.nick + " = " + ch + " :" + names + "\r\n");
        queueSend(fd, ":ircserv 366 " + c.nick + " " + ch + " :End of /NAMES list.\r\n");
        return;
    }

    if (m.command == "PART")
    {
        if (m.params.empty()) { sendNumeric(fd, "461", "PART", "Not enough parameters"); return; }
        std::string ch = m.params[0];

        std::map<std::string, std::set<int> >::iterator itc = _chans.find(ch);
        if (itc == _chans.end() || itc->second.count(fd) == 0) {
            sendNumeric(fd, "442", ch, "You're not on that channel");
            return;
        }

        std::string partMsg = ":" + c.nick + " PART " + ch;
        if (!m.trailing.empty())
            partMsg += " :" + m.trailing;
        partMsg += "\r\n";

        queueSend(fd, partMsg);
        broadcastToChannel(ch, partMsg, fd);

        bool was_op = _chanOps[ch].count(fd);
        itc->second.erase(fd);
        _chanOps[ch].erase(fd);
        _chanInvited[ch].erase(fd);

        if (was_op && !itc->second.empty() && _chanOps[ch].empty())
        {
            int new_op_fd = *itc->second.begin();
            _chanOps[ch].insert(new_op_fd);
            
            Client &new_op_c = _clients[new_op_fd];
            std::string mode_msg = ":" + new_op_c.nick + " MODE " + ch + " +o " + new_op_c.nick + "\r\n";
            broadcastToChannel(ch, mode_msg, -1);
        }

        if (itc->second.empty())
        {
            _chans.erase(itc);
            _chanOps.erase(ch);
            _chanInvited.erase(ch);
            _chanTopicLock.erase(ch);
            _chanKey.erase(ch);
            _chanLimit.erase(ch);
            _topics.erase(ch); 
        }
        return;
    }

    if (m.command == "MODE")
    {
        if (m.params.empty()) { sendNumeric(fd, "461", "MODE", "Not enough parameters"); return; }

        std::string target = m.params[0];
        if (target.empty() || target[0] != '#') {
            sendNumeric(fd, "472", target, "Unknown MODE flag");
            return;
        }

        if (_chans.find(target) == _chans.end()) {
            sendNumeric(fd, "403", target, "No such channel");
            return;
        }

        if (m.params.size() == 1)
        {
            std::string modes = "+";
            if (_chanInviteOnly[target]) modes += "i";
            if (_chanTopicLock[target])  modes += "t";
            if (_chanKey.find(target) != _chanKey.end()) modes += "k";
            if (_chanLimit.find(target) != _chanLimit.end()) modes += "l";

            std::ostringstream resp;
            resp << ":ircserv 324 " << (c.nick.empty() ? "*" : c.nick)
                 << " " << target << " " << modes;
            if (_chanKey.find(target) != _chanKey.end())  resp << " " << _chanKey[target];
            if (_chanLimit.find(target) != _chanLimit.end()) resp << " " << _chanLimit[target];
            resp << "\r\n";
            queueSend(fd, resp.str());
            return;
        }

        if (!isChanOp(target, fd)) {
            sendNumeric(fd, "482", target, "You're not channel operator");
            return;
        }

        std::string fl = m.params[1];
        if (fl.size() < 2 || (fl[0] != '+' && fl[0] != '-')) {
            sendNumeric(fd, "472", fl, "Unknown MODE flag");
            return;
        }
        char sign = fl[0];
        char flag = fl[1];

        if (flag == 't') {
            _chanTopicLock[target] = (sign == '+');
            std::string msg = ":" + c.nick + " MODE " + target + " " + fl + "\r\n";
            queueSend(fd, msg);
            broadcastToChannel(target, msg, fd);
            return;
        }

        if (flag == 'i') {
            _chanInviteOnly[target] = (sign == '+');
            std::string msg = ":" + c.nick + " MODE " + target + " " + fl + "\r\n";
            queueSend(fd, msg);
            broadcastToChannel(target, msg, fd);
            return;
        }

        if (flag == 'k') {
            if (sign == '+') {
                if (m.params.size() < 3) { sendNumeric(fd, "461", "MODE", "Not enough parameters"); return; }
                std::string key = m.params[2];
                _chanKey[target] = key;
                std::string msg = ":" + c.nick + " MODE " + target + " +k " + key + "\r\n";
                queueSend(fd, msg);
                broadcastToChannel(target, msg, fd);
            } else {
                _chanKey.erase(target);
                std::string msg = ":" + c.nick + " MODE " + target + " -k\r\n";
                queueSend(fd, msg);
                broadcastToChannel(target, msg, fd);
            }
            return;
        }

        if (flag == 'l')
        {
            if (sign == '+')
            {
                if (m.params.size() < 3) { sendNumeric(fd, "461", "MODE", "Not enough parameters"); return; }
                int lim = std::atoi(m.params[2].c_str());
                if (lim <= 0) lim = 1;
                _chanLimit[target] = lim;
                std::ostringstream msg;
                msg << ":" << c.nick << " MODE " << target << " +l " << lim << "\r\n";
                queueSend(fd, msg.str());
                broadcastToChannel(target, msg.str(), fd);
            } else {
                _chanLimit.erase(target);
                std::string msg = ":" + c.nick + " MODE " + target + " -l\r\n";
                queueSend(fd, msg);
                broadcastToChannel(target, msg, fd);
            }
            return;
        }

        if (flag == 'o')
        {
            if (m.params.size() < 3) { sendNumeric(fd, "461", "MODE", "Not enough parameters"); return; }
            std::string nickarg = m.params[2];
            int ofd = findFdByNick(nickarg);
            if (ofd < 0 || !isChanMember(target, ofd)) {
                sendNumeric(fd, "441", nickarg + " " + target, "They aren't on that channel");
                return;
            }
            
            if (sign == '+') {
                _chanOps[target].insert(ofd);
            }
            else {
                if (_chanOps[target].count(ofd) && _chanOps[target].size() == 1) {
                    sendNumeric(fd, "482", target, "Cannot remove the last channel operator");
                    return;
                }
                _chanOps[target].erase(ofd);
            }

            std::string msg = ":" + c.nick + " MODE " + target + " " + fl + " " + nickarg + "\r\n";
            queueSend(fd, msg);
            broadcastToChannel(target, msg, fd);
            return;
        }

        sendNumeric(fd, "472", fl, "Unknown MODE flag");
        return;
    }

    if (m.command == "INVITE")
    {
        if (m.params.size() < 2) { sendNumeric(fd, "461", "INVITE", "Not enough parameters"); return; }

        std::string nick = m.params[0];
        std::string ch   = m.params[1];

        if (ch.empty() || ch[0] != '#') { 
            sendNumeric(fd, "461", "INVITE", "Usage: INVITE <nick> <#channel>"); 
            return; 
        }

        int tfd = findFdByNick(nick);
        if (tfd < 0) { sendNumeric(fd, "401", nick, "No such nick"); return; }
        if (_chans.find(ch) == _chans.end()) { sendNumeric(fd, "403", ch, "No such channel"); return; }
        if (!isChanMember(ch, fd)) { sendNumeric(fd, "442", ch, "You're not on that channel"); return; }
        
        if (_chanInviteOnly[ch] && !isChanOp(ch, fd)) { 
            sendNumeric(fd, "482", ch, "You're not channel operator"); 
            return; 
        }

        if (isChanMember(ch, tfd)) { sendNumeric(fd, "443", nick + " " + ch, "is already on channel"); return; }

        _chanInvited[ch].insert(tfd);

        queueSend(fd, ":ircserv 341 " + (c.nick.empty() ? "*" : c.nick) + " " + nick + " " + ch + "\r\n");
        std::string inv = ":" + c.nick + " INVITE " + nick + " :" + ch + "\r\n";
        queueSend(tfd, inv);
        return;
    }

    if (m.command == "KICK")
    {
        if (m.params.size() < 2) { sendNumeric(fd, "461", "KICK", "Not enough parameters"); return; }
        std::string ch   = m.params[0];
        std::string nick = m.params[1];

        if (_chans.find(ch) == _chans.end()) { sendNumeric(fd, "403", ch, "No such channel"); return; }
        if (!isChanMember(ch, fd)) { sendNumeric(fd, "442", ch, "You're not on that channel"); return; }
        if (!isChanOp(ch, fd)) { sendNumeric(fd, "482", ch, "You're not channel operator"); return; }

        int tfd = findFdByNick(nick);
        if (tfd < 0 || !isChanMember(ch, tfd)) {
            sendNumeric(fd, "441", nick + " " + ch, "They aren't on that channel");
            return;
        }

        std::string reason = m.trailing.empty() ? "Kicked" : m.trailing;
        std::string kmsg = ":" + c.nick + " KICK " + ch + " " + nick + " :" + reason + "\r\n";
        queueSend(tfd, kmsg);
        broadcastToChannel(ch, kmsg, tfd);

        _chans[ch].erase(tfd);
        _chanOps[ch].erase(tfd);
        _chanInvited[ch].erase(tfd);
        if (_chans[ch].empty()) {
            _chans.erase(ch);
            _chanOps.erase(ch);
            _chanInvited.erase(ch);
        }
        return;
    }

    if (m.command == "NAMES")
    {
        std::string nick = c.nick.empty() ? "*" : c.nick;

        if (m.params.empty()) {
            for (std::map<std::string, std::set<int> >::const_iterator it = _chans.begin();
                 it != _chans.end(); ++it)
            {
                if (!it->second.count(fd)) continue;
                const std::string &ch = it->first;

                std::string names;
                for (std::set<int>::const_iterator mi = it->second.begin(); mi != it->second.end(); ++mi) {
                    std::map<int, Client>::const_iterator ci = _clients.find(*mi);
                    if (ci != _clients.end() && !ci->second.nick.empty()) {
                        if (!names.empty()) names += " ";
                        names += ci->second.nick;
                    }
                }
                queueSend(fd, ":ircserv 353 " + nick + " = " + ch + " :" + names + "\r\n");
                queueSend(fd, ":ircserv 366 " + nick + " " + ch + " :End of /NAMES list.\r\n");
            }
            return;
        }

        std::string ch = m.params[0];
        std::map<std::string, std::set<int> >::const_iterator itc = _chans.find(ch);

        std::string names;
        if (itc != _chans.end())
        {
            for (std::set<int>::const_iterator it = itc->second.begin(); it != itc->second.end(); ++it)
            {
                std::map<int, Client>::const_iterator ci = _clients.find(*it);
                if (ci != _clients.end() && !ci->second.nick.empty()) {
                    if (!names.empty()) names += " ";
                    names += ci->second.nick;
                }
            }
        }
        queueSend(fd, ":ircserv 353 " + nick + " = " + ch + " :" + names + "\r\n");
        queueSend(fd, ":ircserv 366 " + nick + " " + ch + " :End of /NAMES list.\r\n");
        return;
    }

    if (m.command == "NOTICE")
    {
        if (m.params.empty() || m.trailing.empty()) return;
        std::string target  = m.params[0];
        std::string payload = ":" + c.nick + " NOTICE " + target + " :" + m.trailing + "\r\n";

        if (!target.empty() && target[0] == '#') {
            std::map<std::string, std::set<int> >::iterator itc = _chans.find(target);
            if (itc != _chans.end() && itc->second.count(fd))
                broadcastToChannel(target, payload, fd);
        } else {
            int tfd = findFdByNick(target);
            if (tfd >= 0) queueSend(tfd, payload);
        }
        return;
    }

    if (m.command == "TOPIC")
    {
        if (m.params.empty()) { sendNumeric(fd, "461", "TOPIC", "Not enough parameters"); return; }
        std::string ch = m.params[0];

        if (!isChanMember(ch, fd)) {
            sendNumeric(fd, "442", ch, "You're not on that channel");
            return;
        }

        if (m.trailing.empty()) {
            std::map<std::string, TopicInfo>::const_iterator tp = _topics.find(ch);
            if (tp != _topics.end() && !tp->second.text.empty()) {
                queueSend(fd, ":ircserv 332 " + c.nick + " " + ch + " :" + tp->second.text + "\r\n");
                std::ostringstream wh;
                wh << ":ircserv 333 " << c.nick << " " << ch << " " << tp->second.setter << " " << tp->second.setat << "\r\n";
                queueSend(fd, wh.str());
            } else {
                sendNumeric(fd, "331", ch, "No topic is set");
            }
            return;
        }

        if (_chanTopicLock[ch] && !isChanOp(ch, fd)) {
            sendNumeric(fd, "482", ch, "You're not channel operator");
            return;
        }

        TopicInfo &info = _topics[ch];
        info.text   = m.trailing;
        info.setter = c.nick;
        info.setat  = std::time(0);

        std::string tmsg = ":" + c.nick + " TOPIC " + ch + " :" + info.text + "\r\n";
        queueSend(fd, tmsg);
        broadcastToChannel(ch, tmsg, fd);

        queueSend(fd, ":ircserv 332 " + c.nick + " " + ch + " :" + info.text + "\r\n");
        std::ostringstream wh2;
        wh2 << ":ircserv 333 " << c.nick << " " << ch << " " << info.setter << " " << info.setat << "\r\n";
        queueSend(fd, wh2.str());
        return;
    }

    if (m.command == "WHOIS")
    {
        if (m.params.empty()) { sendNumeric(fd, "431", "", "No nickname given"); return; }
        std::string target = m.params[0];
        int tfd = findFdByNick(target);

        if (tfd < 0) {
            sendNumeric(fd, "401", target, "No such nick");
            sendNumeric(fd, "318", target, "End of /WHOIS list.");
            return;
        }

        const Client &t = _clients[tfd];
        std::string user = t.user.empty() ? "*" : t.user;
        std::string real = t.realname.empty() ? t.nick : t.realname;
        std::string rq   = c.nick.empty() ? "*" : c.nick;
        std::string tn   = t.nick.empty() ? "*" : t.nick;

        std::string line311 = ":ircserv 311 " + rq + " " + tn + " " + user + " localhost * :" + real + "\r\n";
        queueSend(fd, line311);
        sendNumeric(fd, "318", tn, "End of /WHOIS list.");
        return;
    }

    if (m.command == "PRIVMSG")
    {
        if (m.params.empty()) { sendNumeric(fd, "411", "", "No recipient given (PRIVMSG)"); return; }
        if (m.trailing.empty()) { sendNumeric(fd, "412", "", "No text to send"); return; }
        std::string target = m.params[0];
        std::string payload = ":" + c.nick + " PRIVMSG " + target + " :" + m.trailing + "\r\n";

        if (!target.empty() && target[0] == '#')
        {
            std::map<std::string, std::set<int> >::iterator itc = _chans.find(target);
            if (itc == _chans.end() || itc->second.count(fd) == 0) {
                sendNumeric(fd, "404", target, "Cannot send to channel");
                return;
            }
            broadcastToChannel(target, payload, fd);
        } else {
            int tfd = findFdByNick(target);
            if (tfd < 0) { sendNumeric(fd, "401", target, "No such nick"); return; }
            queueSend(tfd, payload);
        }
        return;
    }

    if (m.command == "LIST")
    {
        std::string nick = c.nick.empty() ? "*" : c.nick;
        sendNumeric(fd, "321", nick, "Channel :Users Name");
        for (std::map<std::string, std::set<int> >::const_iterator it = _chans.begin();
            it != _chans.end(); ++it)
        {
            const std::string &ch = it->first;
            std::size_t count = it->second.size();
            std::string topic = _topics[ch].text;

            std::ostringstream oss;
            oss << ch << " " << count;
            sendNumeric(fd, "322", nick + " " + oss.str(), topic);
        }
        sendNumeric(fd, "323", nick, "End of /LIST");
        return;
    }

    if (m.command == "QUIT")
    {
        std::string why = m.trailing.empty()? "Client Quit" : m.trailing;
        disconnect(fd, why);
        return;
    }

    sendNumeric(fd, "421", m.command, "Unknown command");
}
