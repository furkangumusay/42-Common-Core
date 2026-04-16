#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
private:
	std::stack<int> _stack;
	
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	
	bool isOperator(char c) const;
	bool isDigit(char c) const;
	int performOperation(int a, int b, char op) const;

public:
	RPN();
	~RPN();
	
	bool calculate(const std::string& expression);
	int getResult() const;
};

#endif
