#include "Zombie.hpp"

int main()
{
    Zombie* zombie;

    int size = 5;
    zombie = zombieHorde(size, "Zombie");
    for (int i = 0; i < size; i++)
        zombie[i].announce();
    delete[] zombie;
    return (0);
}
