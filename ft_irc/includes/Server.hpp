#ifndef SERVER_HPP
#define SERVER_HPP

#ifndef ECHO_NUMERIC_AS_NOTICE
#define ECHO_NUMERIC_AS_NOTICE 1
#endif

#include <string>
#include <vector>
#include <map>
#include <set>
#include <poll.h>
#include <ctime>

#include "Client.hpp"
#include "Parser.hpp"

struct TopicInfo
{
    std::string text;
    std::string setter;
    std::time_t setat;
    TopicInfo(): setat(0) {}
};

class Server
{
    public:
        Server(int port, const std::string &password);
        ~Server();

        void run();

    private:
        void setupSocket();
        void addPollFd(int fd, short events);
        void removePollFd(int fd);

        void queueSend(int fd, const std::string &data);
        void sendNumeric(int fd, const std::string &code,
                         const std::string &args, const std::string &text);
        void disconnect(int fd, const std::string &why);
        bool nickInUse(const std::string &nick) const;
        int  findFdByNick(const std::string &nick) const;
        void tryRegister(Client &c);
        void broadcastToChannel(const std::string &chan,
                                const std::string &line,
                                int except_fd);
        void handleMessage(int fd, const IRCMessage &m);

        bool isChanMember(const std::string &ch, int fd) const;
        bool isChanOp(const std::string &ch, int fd) const;

    private:
        int _port;
        std::string _password;
        int _listenfd;
        std::vector<struct pollfd> _pfds;

        std::map<int, Client> _clients;

        std::map<std::string, std::set<int> > _chans;

        std::map<std::string, TopicInfo> _topics;

        std::map<std::string, std::set<int> > _chanOps;

        std::map<std::string, bool>        _chanTopicLock;
        std::map<std::string, bool>        _chanInviteOnly;
        std::map<std::string, std::string> _chanKey;
        std::map<std::string, int>         _chanLimit;

        std::map<std::string, std::set<int> > _chanInvited;
};

#endif
