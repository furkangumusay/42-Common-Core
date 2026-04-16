#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main() 
{
    const int numAnimals = 10;
    Animal* animals[numAnimals];

    for (int i = 0; i < numAnimals; ++i)
    {
        if (i < numAnimals / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < numAnimals; ++i)
    {
        std::cout << animals[i]->getType() << " makes sound: ";
        animals[i]->makeSound();
    }

    for (int i = 0; i < numAnimals; ++i)
        delete animals[i];
    return (0);
}