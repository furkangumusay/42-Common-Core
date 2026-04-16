#include "MutantStack.hpp"
#include <iostream>
#include <stack>

int main()
{
    std::cout << "--- Basic MutantStack Test ---" << std::endl;

    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << "Top: " << mstack.top() << std::endl;

    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "\nIterating through MutantStack:" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::cout << "\n--- Copy constructor test ---" << std::endl;
    MutantStack<int> copy(mstack);

    std::cout << "Copy contents:" << std::endl;
    for (MutantStack<int>::iterator cit = copy.begin(); cit != copy.end(); ++cit)
        std::cout << *cit << " ";
    std::cout << std::endl;

    std::cout << "\n--- Assignment operator test ---" << std::endl;
    MutantStack<int> assigned;
    assigned = mstack;
    std::cout << "Assigned top: " << assigned.top() << std::endl;

    std::cout << "\n--- Reverse iteration test ---" << std::endl;
    for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;

    return 0;
}
