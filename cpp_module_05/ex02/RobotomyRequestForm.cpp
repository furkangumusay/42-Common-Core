#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45, "undefined") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45, target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : AForm(other) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    AForm::operator=(other);
    return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::executeAction() const {
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::cout << "Bzzzzzz... drilling noises" << std::endl;
    if (std::rand() % 2 == 0)
        std::cout << getTarget() << " has been robotomized successfully" << std::endl;
    else
        std::cout << "Robotomy failed on " << getTarget() << std::endl;
}
