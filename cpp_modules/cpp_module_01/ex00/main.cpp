#include "Zombie.hpp"

int main()
{
    std::cout << "Creating heapZombie" << std::endl;
    Zombie *heapZombie = new Zombie("heapFoo");
    heapZombie->announce();

    std::cout << "\nCreating stackZombie" << std::endl;
    randomChump("stackBar");

    std::cout << "\n--- Stack Zombie Scope ---" << std::endl;
    {
        Zombie stackZombieInScope("scopedBaz");
        stackZombieInScope.announce();
        std::cout << "Leaving scope..." << std::endl;
    }
    
    std::cout << "\nDeleting heapZombie" << std::endl;
    delete heapZombie;
    return (0);
}