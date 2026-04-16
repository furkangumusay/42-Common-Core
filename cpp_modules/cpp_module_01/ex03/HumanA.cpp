#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon)
{
    std::cout << "HumanA " << _name << ": Created..." << std::endl;
}

HumanA::~HumanA()
{
    std::cout << "HumanA " << _name << ": Destroyed" << std::endl;
}

void HumanA::attack() const
{
    std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}
