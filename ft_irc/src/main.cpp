#include "../includes/Server.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>


int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: ./ircserv <port> [password]\n";
        return 1;
    }
    int port = 0; std::istringstream(argv[1]) >> port;
    if (port <= 0 || port > 65535) { std::cerr << "Invalid port\n"; return 1; }
    std::string password = (argc == 3) ? argv[2] : std::string();


    try
    {
        Server s(port, password);
        std::cout << "Listening on port " << port << (password.empty()?" (no PASS)":" (PASS enabled)") << std::endl;
        s.run();
    } catch (const std::exception &e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }
}