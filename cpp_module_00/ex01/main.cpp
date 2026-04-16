#include "PhoneBook.hpp"

int	safe_getline(std::string &str)
{
	std::getline(std::cin, str);

	if (std::cin.eof())
		return (1);
	return (0);
}

int main()
{
	PhoneBook phone_book;
	std::string input;

	while (true)
	{
		if (std::cin.eof())
			break;
		std::cout << "Please select an option: ADD, SEARCH or EXIT" << std::endl << "> ";
		if (safe_getline(input))
			break;
		if (input == "ADD")
		{
			if (phone_book.add_contact())
				break;
		}
		else if (input == "SEARCH")
		{
			if (phone_book.search_contact())
				break;
		}
		else if (input == "EXIT")
			break;
		else
			std::cout << "Wrong input :(" << std::endl;
	}
	return (0);
}
