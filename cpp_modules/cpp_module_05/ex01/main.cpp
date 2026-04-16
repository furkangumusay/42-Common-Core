#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    Bureaucrat high("High", 5);
    Bureaucrat low("Low", 150);
    Form contract("Contract", 50, 25);

    std::cout << contract << std::endl;
    low.signForm(contract);
    high.signForm(contract);
    std::cout << contract << std::endl;

    try {
        Form invalid("Invalid", 0, 10);
        std::cout << invalid << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Invalid form: " << e.what() << std::endl;
    }

    return (0);
}
