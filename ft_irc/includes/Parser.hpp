#ifndef PARSER_HPP
#define PARSER_HPP


#include <string>
#include <vector>


struct IRCMessage
{
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    std::string trailing;
};


bool parseIRCLine(const std::string &line, IRCMessage &out);


#endif