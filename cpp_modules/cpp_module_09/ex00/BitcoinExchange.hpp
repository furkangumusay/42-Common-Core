#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
    private:
    	std::map<std::string, float> _database;
    
    	BitcoinExchange(const BitcoinExchange& other);
    	BitcoinExchange& operator=(const BitcoinExchange& other);
    
    	bool isValidDate(const std::string& date) const;
    	bool isValidValue(const std::string& valueStr, float& value) const;
    	std::string trim(const std::string& str) const;
    	float getExchangeRate(const std::string& date) const;
    
    public:
    	BitcoinExchange();
    	~BitcoinExchange();
    
    	bool loadDatabase(const std::string& filename);
    	void processInput(const std::string& filename);
};

#endif
