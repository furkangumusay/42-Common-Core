#include "AForm.hpp"
#include "Bureaucrat.hpp"

namespace {
void validateGrade(int grade) {
    if (grade < 1)
        throw AForm::GradeTooHighException();
    if (grade > 150)
        throw AForm::GradeTooLowException();
}
}

AForm::AForm() : _name("Untitled"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150), _target("undefined") {}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target)
    : _name(name),
      _isSigned(false),
      _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute),
      _target(target) {
    validateGrade(_gradeToSign);
    validateGrade(_gradeToExecute);
}

AForm::AForm(const AForm& other)
    : _name(other._name),
      _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign),
      _gradeToExecute(other._gradeToExecute),
      _target(other._target) {}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        _isSigned = other._isSigned;
        _target = other._target;
    }
    return (*this);
}

AForm::~AForm() {}

const   std::string& AForm::getName()    const{ return (_name); }
bool    AForm::getIsSigned()             const{ return (_isSigned); }
int     AForm::getGradeToSign()          const{ return (_gradeToSign); }
int     AForm::getGradeToExecute()       const{ return (_gradeToExecute); }
const   std::string& AForm::getTarget()  const{ return (_target); }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw() {
    return ("Grade is too high!");
}

const char* AForm::GradeTooLowException::what() const throw() {
    return ("Grade is too low!");
}

const char* AForm::FormNotSignedException::what() const throw() {
    return ("Form is not signed");
}

std::ostream& operator<<(std::ostream& out, const AForm& form) {
    out << form.getName() << " (target: " << form.getTarget() << ")"
        << ", signed: " << (form.getIsSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute();
    return (out);
}
