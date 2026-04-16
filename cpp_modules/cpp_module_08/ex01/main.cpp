#include <iostream>
#include "Span.hpp"

int main()
{
    std::cout << "--- Basic Span Test ---" << std::endl;

    try
    {
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;

        try {
            sp.addNumber(42);
        }
        catch (std::exception &e) {
            std::cout << "Error (full): " << e.what() << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << "General error: " << e.what() << std::endl;
    }

    std::cout << "\n--- Error Test: Not enough elements ---" << std::endl;

    try 
    {
        Span test(1);
        test.addNumber(5);
        std::cout << test.shortestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Error (not enough elements): " << e.what() << std::endl;
    }

    return 0;
}
