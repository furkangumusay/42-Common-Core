#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <string>


struct Client
{
    int fd;
    std::string recvbuf;
    std::string sendbuf;
    
    
    std::string nick;
    std::string user;
    std::string realname;
    
    
    bool pass_ok;
    bool registered;
    bool should_close;
    
    
    Client() : fd(-1), pass_ok(false), registered(false), should_close(false) {}
};


#endif