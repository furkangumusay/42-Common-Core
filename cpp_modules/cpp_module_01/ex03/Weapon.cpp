#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type)
{
    std::cout << "Weapon " << _type << ": Created..." << std::endl;
}

Weapon::~Weapon()
{
    std::cout << "Weapon " << _type << ": Destroyed" << std::endl;
}

const std::string& Weapon::getType(void)
{
    return (_type);
}

void Weapon::setType(std::string type)
{
    _type = type;
}
