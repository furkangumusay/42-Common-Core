#include "Dog.hpp"

Dog::Dog()
{
    std::cout << "Constructor called - Dog" << std::endl;
}

Dog::Dog(const Dog &other)
{
    *this = other;
    std::cout << "Copy constructor - Dog" << std::endl;
}

Dog::~Dog()
{
    std::cout << "Destructor - Dog" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other)
        setType(other.getType());
    std::cout << "Assignation operator - Dog" << std::endl;
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Woof" << std::endl;
}
