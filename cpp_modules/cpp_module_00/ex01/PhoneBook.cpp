#include "PhoneBook.hpp"
#include <cstdlib>

PhoneBook::PhoneBook() : _count(0),  _index(0) {}

static bool only_alpha(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isalpha((unsigned char)(str[i])))
            return false;
    }
    return true;
}

static bool only_digit(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit((unsigned char)(str[i])))
            return false;
    }
    return true;
}

static bool only_ascii(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isprint((unsigned char)(str[i])))
            return false;
    }
    return true;
}

int PhoneBook::add_contact()
{
    std::string input;
    Contact     new_contact;

    while (true)
    {
        std::cout << "Enter First Name: ";
        if (safe_getline(input))
            return (1);
        if(input.empty())
            std::cout << "Field cannot be empty. Please try again." << std::endl;
        else if (!only_alpha(input))
            std::cout << "Only alphabetic characters. Please try again." << std::endl;
        else
        {
            new_contact.set_first_name(input);
            break;
        }
    }

    while (true)
    {
        std::cout << "Enter Last Name: ";
        if (safe_getline(input))
            return (1);
        if(input.empty())
            std::cout << "Field cannot be empty. Please try again." << std::endl;
        else if (!only_alpha(input))
            std::cout << "Only alphabetic characters. Please try again." << std::endl;
        else
        {
            new_contact.set_last_name(input);
            break;
        }
    }

    while (true)
    {
        std::cout << "Enter Nickname: ";
        if (safe_getline(input))
            return (1);
        if(input.empty())
            std::cout << "Field cannot be empty. Please try again." << std::endl;
        else if (!only_alpha(input))
            std::cout << "Only alphabetic characters. Please try again." << std::endl;
        else
        {
            new_contact.set_nickname(input);
            break;
        }
    }

    while (true)
    {
        std::cout << "Enter Phone Number: ";
        if (safe_getline(input))
            return (1);
        if(input.empty())
            std::cout << "Field cannot be empty. Please try again." << std::endl;
        else if (!only_digit(input))
            std::cout << "Only digits. Please try again." << std::endl;
        else
        {
            new_contact.set_phone_number(input);
            break;
        }
    }

    while (true)
    {
        std::cout << "Enter Darkest Secret: ";
        if (safe_getline(input))
            return (1);
        if(input.empty())
            std::cout << "Field cannot be empty. Please try again." << std::endl;
        else if (!only_ascii(input))
            std::cout << "Only ASCII characters. Please try again." << std::endl;
        else
        {
            new_contact.set_darkest_secret(input);
            break;
        }
    }
    _contacts[_count] = new_contact;
    if (_index < 8)
        _index++;
    _count++;
    if (_count == 8)
        _count = 0;
    return (0);
}

std::string resize_string(std::string str)
{
	if (str.length() > 10)
	{
		str.resize(9);
		str += ".";
	}
	return str;
}

static void display_contact(Contact contact, int index)
{
    std::cout << std::setw(10) << std::right << index << "|"
              << std::setw(10) << std::right << resize_string(contact.get_first_name()) << "|"
              << std::setw(10) << std::right << resize_string(contact.get_last_name()) << "|"
              << std::setw(10) << std::right << resize_string(contact.get_nickname()) << std::endl;
}

static void display_header()
{
    std::cout << std::setw(10) << std::right << "Index" << "|"
              << std::setw(10) << std::right << "First Name" << "|"
              << std::setw(10) << std::right << "Last Name" << "|"
              << std::setw(10) << std::right << "Nickname" << std::endl;
     std::cout << "----------|----------|----------|----------" << std::endl;
}

static void display_contact_details(Contact contact, int index)
{
    std::cout << "--- Contact Details (Index: " << index << ") ---" << std::endl;
    std::cout << "First Name:     " << contact.get_first_name() << std::endl;
    std::cout << "Last Name:      " << contact.get_last_name() << std::endl;
    std::cout << "Nickname:       " << contact.get_nickname() << std::endl;
    std::cout << "Phone Number:   " << contact.get_phone_number() << std::endl;
    std::cout << "Darkest Secret: " << contact.get_darkest_secret() << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

int PhoneBook::search_contact()
{
    if (_index == 0)
    {
        std::cout << "PhoneBook is empty." << std::endl;
        return 0;
    }
    display_header();
    for (int i = 0; i < _index; ++i)
    {
        display_contact(_contacts[i], i);
    }
    std::cout << "-------------------------------------------" << std::endl;

    std::string input;
    int user;

    while (true)
    {
        std::cout << "Please select an user: ";
        if (safe_getline(input))
            return (1);
        if (input.empty())
            break;
        if (!only_digit(input))
        {
            std::cout << "Only digits. Please try again." << std::endl;
            continue;
        }
        user = std::atoi(input.c_str());
        if (_index > user && user >= 0)
        {
            display_contact_details(_contacts[user], user);
            break;
        }
        else
            std::cout << "Invalid index." << std::endl;
    }
    return (0);
}
