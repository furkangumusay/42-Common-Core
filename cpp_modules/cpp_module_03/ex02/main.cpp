#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "===== Creating Different Traps =====" << std::endl;
    ClapTrap clap("Clappy");
    ScavTrap scav("Scavvy");
    FragTrap frag("Fraggy");
    
    std::cout << "\n===== Testing Basic Stats =====" << std::endl;
    std::cout << "ClapTrap " << clap.getName() << " has " << clap.getHitPoints() << " hit points, " 
              << clap.getEnergyPoints() << " energy points, and " << clap.getAttackDamage() << " attack damage." << std::endl;
    std::cout << "ScavTrap " << scav.getName() << " has " << scav.getHitPoints() << " hit points, " 
              << scav.getEnergyPoints() << " energy points, and " << scav.getAttackDamage() << " attack damage." << std::endl;
    std::cout << "FragTrap " << frag.getName() << " has " << frag.getHitPoints() << " hit points, " 
              << frag.getEnergyPoints() << " energy points, and " << frag.getAttackDamage() << " attack damage." << std::endl;
    
    std::cout << "\n===== Testing Basic Actions =====" << std::endl;
    clap.attack("Target A");
    scav.attack("Target B");
    frag.attack("Target C");
    
    std::cout << "\n===== Testing Special Abilities =====" << std::endl;
    scav.guardGate();
    frag.highFivesGuys();
    
    std::cout << "\n===== Testing Combat Capabilities =====" << std::endl;
    frag.takeDamage(50);
    frag.beRepaired(20);
    frag.takeDamage(80);
    frag.beRepaired(10);
    
    std::cout << "\n===== Testing Construction and Destruction Chaining =====" << std::endl;
    {
        std::cout << "Creating a temporary FragTrap..." << std::endl;
        FragTrap tempFrag("TempFrag");
        std::cout << "Temporary FragTrap will be destroyed now..." << std::endl;
    }
    
    std::cout << "\n===== Testing Copy Constructor =====" << std::endl;
    FragTrap fragCopy(frag);
    std::cout << "Original FragTrap: " << frag.getName() << std::endl;
    std::cout << "Copied FragTrap: " << fragCopy.getName() << std::endl;
    
    std::cout << "\n===== End of Tests =====" << std::endl;
    return 0;
}