#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_database = other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& str) const
{
	size_t start = 0;
	size_t end = str.length();
	
	while (start < end && (str[start] == ' ' || str[start] == '\t'))
		start++;
    while (end > start &&
           (str[end - 1] == ' ' ||
            str[end - 1] == '\t' ||
            str[end - 1] == '\n' ||
            str[end - 1] == '\r'))
    {
        end--;
    }
	return (str.substr(start, end - start));
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return (false);
	
	if (date[4] != '-' || date[7] != '-')
		return (false);
	
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	}
	
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());
	
	if (year < 2009 || year > 2025)
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeap ? 29 : 28))
			return (false);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day > 30)
			return (false);
	return (true);
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const
{
	std::string trimmed = trim(valueStr);
	
	if (trimmed.empty())
		return (false);
	
	char* end;
	value = strtof(trimmed.c_str(), &end);
	
	if (*end != '\0' && *end != '\n' && *end != '\r')
		return (false);
	
	return (true);
}

bool BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return (false);
	}
	
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;
		
		std::string date = trim(line.substr(0, commaPos));
		std::string valueStr = trim(line.substr(commaPos + 1));
		
		if (!isValidDate(date))
			continue;
		
		float value;
		if (!isValidValue(valueStr, value))
			continue;
		
		_database[date] = value;
	}
	
	file.close();
	return (true);
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _database.find(date);

	if (it != _database.end())
		return (it->second);
	
	it = _database.lower_bound(date);
	if (it == _database.begin())
		return (0);
	
	--it;
	return (it->second);
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	
	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line))
	{
		if (firstLine)
		{
			firstLine = false;
			continue;
		}
		
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << trim(line) << std::endl;
			continue;
		}
		
		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 1));
		
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		
		float value;
		if (!isValidValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		
		float rate = getExchangeRate(date);
		float result = value * rate;
		
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	
	file.close();
}
