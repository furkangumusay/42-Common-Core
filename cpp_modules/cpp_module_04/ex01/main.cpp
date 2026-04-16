#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main()
{
    const int N = 10;
    Animal* animals[N];

    // Dizinin yarısını Dog, yarısını Cat ile doldur
    for (int i = 0; i < N; ++i)
    {
        if (i < N/2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    // Tür ve ses testi
    for (int i = 0; i < N; ++i) {
        std::cout << animals[i]->getType() << " makes sound: ";
        animals[i]->makeSound();
    }

    // Belleği temizle
    for (int i = 0; i < N; ++i)
        delete animals[i];

    // Derin kopya testi
    Dog original;
    Dog copy = original;
    std::cout << "After copy, original and copy still make sounds:\n";
    original.makeSound();
    copy.makeSound();

    return 0;
}
