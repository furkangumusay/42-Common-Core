#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    std::cout << "===== Creating ClapTrap and ScavTrap =====" << std::endl;
    ClapTrap clap("Clappy");
    ScavTrap scav("Scavvy");
    
    std::cout << "\n===== Testing Basic Stats =====" << std::endl;
    std::cout << "ClapTrap " << clap.getName() << " has " << clap.getHitPoints() << " hit points and " 
              << clap.getEnergyPoints() << " energy points." << std::endl;
    std::cout << "ScavTrap " << scav.getName() << " has " << scav.getHitPoints() << " hit points and " 
              << scav.getEnergyPoints() << " energy points." << std::endl;
    
    std::cout << "\n===== Testing Attack Methods =====" << std::endl;
    clap.attack("Target A");
    scav.attack("Target B");
    
    std::cout << "\n===== Testing ScavTrap Special Ability =====" << std::endl;
    scav.guardGate();
    
    std::cout << "\n===== Testing Damage and Repair =====" << std::endl;
    scav.takeDamage(30);
    scav.beRepaired(15);
    
    std::cout << "\n===== Testing Construction and Destruction Chaining =====" << std::endl;
    {
        std::cout << "Creating a temporary ScavTrap..." << std::endl;
        ScavTrap tempScav("TempScav");
        std::cout << "Temporary ScavTrap will be destroyed now..." << std::endl;
    }
    
    std::cout << "\n===== Testing Copy Constructor =====" << std::endl;
    ScavTrap scavCopy(scav);
    std::cout << "Original ScavTrap: " << scav.getName() << std::endl;
    std::cout << "Copied ScavTrap: " << scavCopy.getName() << std::endl;
    
    scavCopy.attack("Different Target");
    
    std::cout << "\n===== End of Tests =====" << std::endl;
    return 0;
}
