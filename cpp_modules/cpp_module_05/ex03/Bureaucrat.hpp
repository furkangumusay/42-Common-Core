#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <exception>
#include <iostream>

class AForm;

class Bureaucrat {
private:
    const   std::string _name;
    int     _grade;

public:
    Bureaucrat();
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

//  Getters
    const   std::string& getName() const;
    int     getGrade() const;

//  Grade Modifiers
    void    incrementGrade();
    void    decrementGrade();

//  Form Processing
    void    signForm(AForm& form) const;
    void    executeForm(AForm const& form) const;

//  Exceptions
    class GradeTooHighException : public std::exception {
        public:
        const char* what() const throw() {
            return ("Grade is too high!");
        }
    };

    class GradeTooLowException : public std::exception {
        public:
        const char* what() const throw() {
            return ("Grade is too low!");
        }
    };

};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b);

#endif
