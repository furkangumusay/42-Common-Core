#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int intValue)
{
    _value = intValue << fracBits;
}

Fixed::Fixed(const float floatValue)
{
    _value = roundf(floatValue * (1 << fracBits));
}

Fixed::Fixed(const Fixed &other)
{
    *this = other;
}

Fixed& Fixed::operator=(const Fixed &other)
{
    if (this != &other)
        _value = other.getRawBits();
    return (*this);
}

Fixed::~Fixed() {}

int Fixed::getRawBits( void ) const
{
    return (_value);
}

void Fixed::setRawBits( int const raw )
{
    this->_value = raw;
}

float Fixed::toFloat( void ) const
{
    return (float)this->_value / (float)(1 << fracBits);
}

int Fixed::toInt( void ) const
{
    return this->_value >> fracBits;
}

bool Fixed::operator>(const Fixed &other) const
{
    return this->_value > other.getRawBits();
}

bool Fixed::operator<(const Fixed &other) const
{
    return this->_value < other.getRawBits();
}

bool Fixed::operator>=(const Fixed &other) const
{
    return this->_value >= other.getRawBits();
}

bool Fixed::operator<=(const Fixed &other) const
{
    return this->_value <= other.getRawBits();
}

bool Fixed::operator==(const Fixed &other) const
{
    return this->_value == other.getRawBits();
}

bool Fixed::operator!=(const Fixed &other) const
{
    return this->_value != other.getRawBits();
}

Fixed Fixed::operator+(const Fixed &other) const
{
    Fixed result;
    result.setRawBits(this->_value + other.getRawBits());
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const
{
    Fixed result;
    result.setRawBits(this->_value - other.getRawBits());
    return result;
}

Fixed Fixed::operator*(const Fixed &other) const
{
    Fixed result;
    long long temp_val = (long long)this->_value * (long long)other.getRawBits();
    result.setRawBits(temp_val >> fracBits);
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
    Fixed result;
    long long temp_val = (long long)this->_value << fracBits;
    result.setRawBits(temp_val / other.getRawBits());
    return result;
}

Fixed& Fixed::operator++()
{
    this->_value++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed temp(*this);
    this->_value++;
    return temp;
}

Fixed& Fixed::operator--()
{
    this->_value--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed temp(*this);
    this->_value--;
    return temp;
}

Fixed& Fixed::min(Fixed &a, Fixed &b)
{
    return ((a < b) ? a : b);
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b)
{
    return ((a < b) ? a : b);
}

Fixed& Fixed::max(Fixed &a, Fixed &b)
{
    return ((a > b) ? a : b);
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b)
{
    return ((a > b) ? a : b);
}

std::ostream& operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}
