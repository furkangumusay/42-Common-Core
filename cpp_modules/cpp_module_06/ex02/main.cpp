#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void) {
	std::srand(std::time(0));
	int random = std::rand() % 3;
	
	switch (random) {
		case 0:
			std::cout << "[generate] Created A" << std::endl;
			return (new A());
		case 1:
			std::cout << "[generate] Created B" << std::endl;
			return (new B());
		case 2:
			std::cout << "[generate] Created C" << std::endl;
			return (new C());
		default:
			return (NULL);
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (std::exception&) {}
	
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (std::exception&) {}
	
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (std::exception&) {}
}

int main() {
	Base* obj = generate();
	
	std::cout << "\nIdentify by pointer: ";
	identify(obj);
	
	std::cout << "Identify by reference: ";
	identify(*obj);
	
	delete obj;
	
	std::cout << "\n--- Multiple tests ---" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "\nTest " << i + 1 << ":" << std::endl;
		Base* test = generate();
		std::cout << "  Pointer: ";
		identify(test);
		std::cout << "  Reference: ";
		identify(*test);
		delete test;
	}
	
	return (0);
}
