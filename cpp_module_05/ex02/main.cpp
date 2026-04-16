#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    Bureaucrat boss("Boss", 1);
    Bureaucrat clerk("Clerk", 70);
    Bureaucrat intern("Intern", 150);

    ShrubberyCreationForm shrub("park");
    RobotomyRequestForm robot("Bender");
    PresidentialPardonForm pardon("Arthur");

    intern.signForm(robot);
    clerk.signForm(shrub);
    boss.signForm(robot);
    boss.signForm(pardon);

    clerk.executeForm(shrub);
    boss.executeForm(robot);
    boss.executeForm(pardon);

    return (0);
}
