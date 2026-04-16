#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat;

class AForm {
private:
    const       std::string _name;
    bool        _isSigned;
    const int   _gradeToSign;
    const int   _gradeToExecute;
    std::string _target;
protected:
    virtual void executeAction() const = 0;

public:
    AForm();
    AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

// Getters
    const   std::string& getName() const;
    bool    getIsSigned() const;
    int     getGradeToSign() const;
    int     getGradeToExecute() const;
    const   std::string& getTarget() const;

// Form operations
    void    beSigned(const Bureaucrat& bureaucrat);
    void    execute(const Bureaucrat& executor) const;

// Exceptions
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
