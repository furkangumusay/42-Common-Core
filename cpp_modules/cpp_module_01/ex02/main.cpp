#include <iostream>

int main()
{
    std::string brainString = "HI THIS IS BRAIN";

    std::string* stringPTR = &brainString;

    std::string& stringREF = brainString;

    std::cout << "---- Memory Addresses ----" << std::endl;
    std::cout << "Address of brainString: " << &brainString << std::endl;
    std::cout << "Address held by stringPTR: " << stringPTR << std::endl;
    std::cout << "Address held by stringREF: " << &stringREF << std::endl;

    std::cout << "\n--- Values ---" << std::endl;
    std::cout << "Value of brainString:   " << brainString << std::endl;
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value referred to by stringREF: " << stringREF << std::endl;
    return (0);
}
