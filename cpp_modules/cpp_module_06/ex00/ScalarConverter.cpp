#include "ScalarConverter.hpp"
#include <cerrno>
#include <climits>
#include <iomanip>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { 
	(void)other; 
	return (*this); 
}
ScalarConverter::~ScalarConverter() {}

namespace {
	void printImpossibleAll() {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}

	void printChar(double value) {
		if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
			std::cout << "char: impossible" << std::endl;
		else if (!isprint(static_cast<int>(value)))
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}

	void printInt(double value) {
		if (std::isnan(value) || std::isinf(value) || value > INT_MAX || value < INT_MIN)
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(value) << std::endl;
	}

	void printFloat(double value) {
		std::cout << "float: " << std::fixed << std::setprecision(1) 
		          << static_cast<float>(value) << "f" << std::endl;
	}

	void printDouble(double value) {
		std::cout << "double: " << std::fixed << std::setprecision(1) 
		          << value << std::endl;
	}

	void printAllFromDouble(double value) {
		printChar(value);
		printInt(value);
		printFloat(value);
		printDouble(value);
	}
}

bool ScalarConverter::isChar(const std::string& literal) {
	return (literal.length() == 1 
	        && !isdigit(static_cast<unsigned char>(literal[0])) 
	        && isprint(static_cast<unsigned char>(literal[0])));
}

bool ScalarConverter::isInt(const std::string& literal) {
	if (literal.empty())
		return (false);
	
	size_t start = 0;
	if (literal[0] == '+' || literal[0] == '-')
		start = 1;
	
	if (start >= literal.length())
		return (false);
	
	for (size_t i = start; i < literal.length(); i++) {
		if (!isdigit(static_cast<unsigned char>(literal[i])))
			return (false);
	}
	return (true);
}

bool ScalarConverter::isFloat(const std::string& literal) {
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return (false);
	
	std::string withoutF = literal.substr(0, literal.length() - 1);
	if (withoutF.empty())
		return (false);
	
	size_t start = 0;
	if (withoutF[0] == '+' || withoutF[0] == '-')
		start = 1;
	
	bool hasDot = false;
	bool hasDigit = false;
	
	for (size_t i = start; i < withoutF.length(); i++) {
		if (withoutF[i] == '.') {
			if (hasDot)
				return (false);
			hasDot = true;
		} else if (isdigit(static_cast<unsigned char>(withoutF[i]))) {
			hasDigit = true;
		} else {
			return (false);
		}
	}
	return (hasDigit);
}

bool ScalarConverter::isDouble(const std::string& literal) {
	if (literal.empty())
		return (false);
	
	size_t start = 0;
	if (literal[0] == '+' || literal[0] == '-')
		start = 1;
	
	bool hasDot = false;
	bool hasDigit = false;
	
	for (size_t i = start; i < literal.length(); i++) {
		if (literal[i] == '.') {
			if (hasDot)
				return (false);
			hasDot = true;
		} else if (isdigit(static_cast<unsigned char>(literal[i]))) {
			hasDigit = true;
		} else {
			return (false);
		}
	}
	return (hasDigit && hasDot);
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
	return (literal == "nan" || literal == "nanf" || 
	        literal == "+inf" || literal == "+inff" ||
	        literal == "-inf" || literal == "-inff" ||
	        literal == "inf" || literal == "inff");
}

void ScalarConverter::convertFromChar(const std::string& literal) {
	char c = literal[0];
	double value = static_cast<double>(c);
	
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	printFloat(value);
	printDouble(value);
}

void ScalarConverter::convertFromInt(const std::string& literal) {
	errno = 0;
	char* end;
	long value = strtol(literal.c_str(), &end, 10);
	
	if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
		printImpossibleAll();
		return;
	}
	
	double doubleValue = static_cast<double>(value);
	printAllFromDouble(doubleValue);
}

void ScalarConverter::convertFromFloat(const std::string& literal) {
	std::string withoutF = literal.substr(0, literal.length() - 1);
	errno = 0;
	char* end;
	float floatValue = strtof(withoutF.c_str(), &end);
	
	if (errno == ERANGE) {
		printImpossibleAll();
		return;
	}
	
	double doubleValue = static_cast<double>(floatValue);
	printAllFromDouble(doubleValue);
}

void ScalarConverter::convertFromDouble(const std::string& literal) {
	errno = 0;
	char* end;
	double doubleValue = strtod(literal.c_str(), &end);
	
	if (errno == ERANGE) {
		printImpossibleAll();
		return;
	}
	
	printAllFromDouble(doubleValue);
}

void ScalarConverter::convertPseudoLiteral(const std::string& literal) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	
	if (literal == "nanf" || literal == "nan") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	} else if (literal == "+inff" || literal == "+inf" || literal == "inff" || literal == "inf") {
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	} else if (literal == "-inff" || literal == "-inf") {
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}

void ScalarConverter::convert(const std::string& literal) {
	if (literal.empty()) {
		std::cout << "Error: empty literal" << std::endl;
		return;
	}

	if (isPseudoLiteral(literal))
		convertPseudoLiteral(literal);
	else if (isChar(literal))
		convertFromChar(literal);
	else if (isInt(literal))
		convertFromInt(literal);
	else if (isFloat(literal))
		convertFromFloat(literal);
	else if (isDouble(literal))
		convertFromDouble(literal);
	else 
		std::cout << "Error: invalid literal" << std::endl;
}
