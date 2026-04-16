#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(T const &elem)
{
    std::cout << elem << " ";
}

void incrementInt(int &n)
{
    n += 1;
}

int main()
{
    std::cout << "--- int array ---" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    ::iter(arr, 5, printElement<int>);
    std::cout << std::endl;

    std::cout << "after increment: ";
    ::iter(arr, 5, incrementInt);
    ::iter(arr, 5, printElement<int>);
    std::cout << "\n" << std::endl;

    std::cout << "--- string array ---" << std::endl;
    std::string words[] = {"hello", "world", "cpp", "module"};
    ::iter(words, 4, printElement<std::string>);
    std::cout << "\n" << std::endl;

    std::cout << "--- const array ---" << std::endl;
    const int constArr[] = {10, 20, 30};
    ::iter(constArr, 3, printElement<int>);
    std::cout << "\n";

    return 0;
}
