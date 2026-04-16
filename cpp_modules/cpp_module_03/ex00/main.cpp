#include "ClapTrap.hpp"

int main()
{
    std::cout << "=== Creating ClapTraps ===\n";
    ClapTrap defaultClap;
    ClapTrap clap1("Clappy");
    ClapTrap clap2("Trappy");

    std::cout << "\n=== Testing Energy Consumption ===\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Energy points left: " << clap1.getEnergyPoints() << std::endl;
        clap1.attack("Target Dummy");
    }
    clap1.attack("Target Dummy");

    std::cout << "\n=== Testing Hit Points ===\n";
    clap2.takeDamage(5);
    clap2.beRepaired(2);
    clap2.takeDamage(7);
    clap2.beRepaired(5);
    clap2.attack("Target Dummy");

    std::cout << ("\n=== Testing Copy Constructor ===\n");
    ClapTrap clap3(clap1);
    std::cout << "Copied ClapTrap name: " << clap3.getName() << std::endl;
    std::cout << "Copied ClapTrap energy points: " << clap3.getEnergyPoints() << std::endl;
    std::cout << ("=== ---------------------------- ===\n");
    return (0);
}