#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
    std::cout << "Default constructor - Animal" << std::endl;
}

Animal::Animal(const Animal& other) : _type(other._type)
{
    std::cout << "Copy constructor - Animal" << std::endl;
}

Animal::~Animal()
{
    std::cout << "Destructor called - Animal" << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
    if (this != &other)
        _type = other._type;
    std::cout << "Assignation operator - Animal" << std::endl;
    return (*this);
}

void Animal::setType(const std::string type)
{
    _type = type;
}

const std::string Animal::getType(void) const
{
    return (_type);
}

void Animal::makeSound() const
{
    std::cout << "Animal Sound" << std::endl;
}