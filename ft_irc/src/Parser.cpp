#include "../includes/Parser.hpp"
#include <cctype>


static std::string trim(const std::string &s) {
    std::string::size_type i = 0, j = s.size();
    while (i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')) ++i;
    while (j > i && (s[j-1] == ' ' || s[j-1] == '\t' || s[j-1] == '\r' || s[j-1] == '\n')) --j;
    return s.substr(i, j - i);
}

static void toUpper(std::string &s) {
    for (std::string::size_type i=0;i<s.size();++i) s[i] = std::toupper(static_cast<unsigned char>(s[i]));
}

bool parseIRCLine(const std::string &lineIn, IRCMessage &out) {
    out = IRCMessage();
    std::string line = trim(lineIn);
    if (line.empty()) return false;

    std::string::size_type i = 0, n = line.size();

    if (line[0] == ':')
    {
        std::string::size_type sp = line.find(' ');
        if (sp == std::string::npos) return false;
            out.prefix = line.substr(1, sp - 1);
        i = sp + 1;
        while (i < n && line[i] == ' ') ++i;
    }


    std::string::size_type sp = line.find(' ', i);
    if (sp == std::string::npos)
    {
        out.command = line.substr(i);
        toUpper(out.command);
        return true;
    }
    else
    {
        out.command = line.substr(i, sp - i);
        toUpper(out.command);
        i = sp + 1;
    }


    while (i < n)
    {
        while (i < n && line[i] == ' ') ++i;
        if (i >= n) break;
        if (line[i] == ':') {
            out.trailing = line.substr(i + 1);
            break;
        }
        std::string::size_type sp2 = line.find(' ', i);
        if (sp2 == std::string::npos)
        {
            out.params.push_back(line.substr(i));
            break;
        } else {
            out.params.push_back(line.substr(i, sp2 - i));
            i = sp2 + 1;
        }
    }
    return true;
}