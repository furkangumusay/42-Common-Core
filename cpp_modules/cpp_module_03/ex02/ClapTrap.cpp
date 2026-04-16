#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Default"),  _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap default constructor called." << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap named constructor called for " << _name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
    std::cout << "ClapTrap copy constuctor called." << std::endl;
    *this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cout << "ClapTrap assignment operator called." << std::endl;
    if (this != &other)
    {
        _name = other._name;
        _hitPoints = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap destructor called for " << _name << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (_energyPoints == 0)
    {
        std::cout << "ClapTrap " << _name  << " has no energy points left to attack!\n";
        return;
    }
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " has no hit points left and cannot attack!\n";
        return;
    }
    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " is already defeated and cannot take more damage!\n";
        return;
    }
    if (amount >= _hitPoints)
    {
        _hitPoints = 0;
        std::cout << "ClapTrap " << _name << " takes " << amount << " damage and is defeated!\n";
    }
    else
    {
        _hitPoints -= amount;
        std::cout << "ClapTrap " << _name << " takes " << amount << " damage, reducing hit points to " << _hitPoints << "!\n";
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (_energyPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " has no energy points left to repair itself!\n";
        return;
    }
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " has no hit points left and cannot repair itself!\n";
        return;
    }
    _energyPoints--;
    _hitPoints += amount;
    std::cout << "ClapTrap " << _name << " repairs itself for " << amount << " hit points, now has " << _hitPoints << " hit points!\n";
}

std::string ClapTrap::getName() const
{
    return (_name);
}

unsigned int ClapTrap::getHitPoints() const
{
    return (_hitPoints);
}

unsigned int ClapTrap::getEnergyPoints() const
{
    return (_energyPoints);
}

unsigned int ClapTrap::getAttackDamage() const
{
    return (_attackDamage);
}
