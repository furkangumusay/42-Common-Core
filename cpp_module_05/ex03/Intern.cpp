#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>
#include <cstddef>

Intern::Intern() {}

Intern::Intern(const Intern& other) {
    (void)other;
}

Intern& Intern::operator=(const Intern& other) {
    (void)other;
    return (*this);
}

Intern::~Intern() {}

namespace {
struct FormEntry {
    const char* name;
    AForm* (*create)(const std::string& target);
};

AForm* createShrubbery(const std::string& target) {
    return (new ShrubberyCreationForm(target));
}

AForm* createRobotomy(const std::string& target) {
    return (new RobotomyRequestForm(target));
}

AForm* createPardon(const std::string& target) {
    return (new PresidentialPardonForm(target));
}
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    const FormEntry entries[3] = {
        {"shrubbery creation", &createShrubbery},
        {"robotomy request", &createRobotomy},
        {"presidential pardon", &createPardon}
    };

    for (int i = 0; i < 3; ++i) {
        if (formName == entries[i].name) {
            AForm* form = entries[i].create(target);
            std::cout << "Intern creates " << entries[i].name << std::endl;
            return (form);
        }
    }

    std::cout << "Intern cannot create " << formName << " because it does not exist." << std::endl;
    return (NULL);
}
