#include "Animal.hpp"

Animal::Animal(): _type("Animal")
{
    std::cout << "Animal constructed" << std::endl;
}

Animal::Animal(const Animal& other) : _type(other._type)
{
    std::cout << "Animal copy constructed" << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
    if (this != &other)
        _type = other._type;
    std::cout << "Animal assigned" << std::endl;
    return (*this);
}

Animal::~Animal()
{
    std::cout << "Animal destructed" << std::endl;
}

void Animal::setType(const std::string type)
{
    _type = type;
}

const std::string Animal::getType() const
{
    return (_type);
}
