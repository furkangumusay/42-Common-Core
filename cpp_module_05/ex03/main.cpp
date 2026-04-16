#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

namespace {
void handleForm(AForm* form, Bureaucrat& junior, Bureaucrat& senior) {
    if (!form)
        return;
    junior.signForm(*form);
    senior.signForm(*form);
    junior.executeForm(*form);
    senior.executeForm(*form);
}
}

int main() {
    Intern intern;
    Bureaucrat senior("Senior", 5);
    Bureaucrat junior("Junior", 140);

    AForm* shrub = intern.makeForm("shrubbery creation", "garden");
    AForm* robot = intern.makeForm("robotomy request", "Bender");
    AForm* pardon = intern.makeForm("presidential pardon", "Arthur");
    intern.makeForm("coffee", "Office");

    handleForm(shrub, junior, senior);
    handleForm(robot, junior, senior);
    handleForm(pardon, junior, senior);

    delete shrub;
    delete robot;
    delete pardon;

    return (0);
}
