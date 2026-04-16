#include "RPN.hpp"
#include <iostream>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
	}
	return (*this);
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

int RPN::performOperation(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return (a / b);
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}

bool RPN::calculate(const std::string& expression)
{
	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token)
	{
		if (token.length() == 1 && isDigit(token[0]))
		{
			_stack.push(token[0] - '0');
		}
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return (false);
			}
			
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			
			try
			{
				int result = performOperation(a, b, token[0]);
				_stack.push(result);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				return (false);
			}
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return (false);
		}
	}
	
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return (false);
	}
	
	return (true);
}

int RPN::getResult() const
{
	if (_stack.empty())
		return (0);
	return (_stack.top());
}
