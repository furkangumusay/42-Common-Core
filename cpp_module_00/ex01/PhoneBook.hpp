#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"


class PhoneBook
{
    private:
    Contact _contacts[8];
    int     _count;
    int     _index;
    
    public:
    PhoneBook();
    int add_contact();
    int search_contact();
};

int safe_getline(std::string &str);
#endif
