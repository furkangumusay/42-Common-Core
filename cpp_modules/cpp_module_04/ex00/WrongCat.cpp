#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	setType("WrongCat");
	std::cout << "Default constructor - WrongCat" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other)
{
	*this = other;
	std::cout << "Copy constructor - WrongCat" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "Destructor - WrongCat" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
	if (this != &other)
		this->setType(other.getType());
	std::cout << "Assignation operator - WrongCat" << std::endl;
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "WrongCat sound" << std::endl;
}
