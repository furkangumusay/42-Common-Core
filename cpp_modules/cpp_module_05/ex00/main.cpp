#include "Bureaucrat.hpp"

namespace {
void tryPromote(Bureaucrat& bureaucrat) {
    try {
        bureaucrat.incrementGrade();
        std::cout << "Promoted: " << bureaucrat << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Promotion failed: " << e.what() << std::endl;
    }
}

void tryDemote(Bureaucrat& bureaucrat) {
    try {
        bureaucrat.decrementGrade();
        std::cout << "Demoted: " << bureaucrat << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Demotion failed: " << e.what() << std::endl;
    }
}
}

int main() {
    try {
        Bureaucrat chief("Chief", 1);
        std::cout << chief << std::endl;
        tryPromote(chief);
    } catch (const std::exception& e) {
        std::cout << "Chief error: " << e.what() << std::endl;
    }

    try {
        Bureaucrat trainee("Trainee", 150);
        std::cout << trainee << std::endl;
        tryDemote(trainee);
    } catch (const std::exception& e) {
        std::cout << "Trainee error: " << e.what() << std::endl;
    }

    try {
        Bureaucrat ghost("Ghost", 151);
        std::cout << ghost << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ghost error: " << e.what() << std::endl;
    }

    return (0);
}
