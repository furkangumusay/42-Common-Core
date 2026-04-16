#include "easyfind.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

template <typename T>
void testContainer(T &container, int value, const std::string &name)
{
    std::cout << "--- Testing " << name << " ---" << std::endl;
    
    try {
        typename T::iterator it = easyfind(container, value);
        std::cout << "Found: " << *it << std::endl;
    } 
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    // VECTOR
    int arr_vec[] = {1, 2, 3, 42};
    std::vector<int> vec(arr_vec, arr_vec + sizeof(arr_vec) / sizeof(arr_vec[0]));
    testContainer(vec, 42, "std::vector");
    testContainer(vec, 99, "std::vector (not found)");

    // LIST
    int arr_lst[] = {10, 20, 30};
    std::list<int> lst(arr_lst, arr_lst + sizeof(arr_lst) / sizeof(arr_lst[0]));
    testContainer(lst, 20, "std::list");
    testContainer(lst, -5, "std::list (not found)");

    // DEQUE
    int arr_dq[] = {100, 200, 300};
    std::deque<int> dq(arr_dq, arr_dq + sizeof(arr_dq) / sizeof(arr_dq[0]));
    testContainer(dq, 300, "std::deque");
    testContainer(dq, 12345, "std::deque (not found)");

    return 0;
}