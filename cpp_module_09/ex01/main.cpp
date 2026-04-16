#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	
	RPN rpn;
	
	if (rpn.calculate(argv[1]))
	{
		std::cout << rpn.getResult() << std::endl;
		return (0);
	}
	
	return (1);
}
