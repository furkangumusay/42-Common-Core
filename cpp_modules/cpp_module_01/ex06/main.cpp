#include "Harl.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./harlFilter <level>" << std::endl;
        return 1;
    }

    Harl harl;
    std::string level = argv[1];

    if (level == "DEBUG")
        harl.complain("DEBUG");
    else if (level == "INFO")
        harl.complain("INFO");
    else if (level == "WARNING")
        harl.complain("WARNING");
    else if (level == "ERROR")
        harl.complain("ERROR");
    else
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    return (0);
}
