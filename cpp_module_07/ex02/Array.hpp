#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>

template <typename T>
class Array
{
	private:
		T*				_elements;
		unsigned int	_size;

	public:
		Array(void) : _elements(NULL), _size(0) {}

		Array(unsigned int n) : _elements(NULL), _size(n) {
			if (n > 0)
				_elements = new T[n];
		}

		Array(Array const& src) : _elements(NULL), _size(0) {
			*this = src;
		}

		~Array(void) {
			if (_elements != NULL)
				delete[] _elements;
		}

		Array& operator=(Array const& rhs) {
			if (this != &rhs)
			{
				if (_elements != NULL)
					delete[] _elements;
				
				_size = rhs._size;
				
				if (_size > 0)
				{
					_elements = new T[_size];
					for (unsigned int i = 0; i < _size; i++)
						_elements[i] = rhs._elements[i];
				}
				else
					_elements = NULL;
			}
			return (*this);
		}

		T& operator[](unsigned int index) {
			if (index >= _size)
				throw OutOfBoundsException();
			return (_elements[index]);
		}

		T const& operator[](unsigned int index) const {
			if (index >= _size)
				throw OutOfBoundsException();
			return (_elements[index]);
		}

		unsigned int size(void) const {
			return (_size);
		}

		class OutOfBoundsException : public std::exception {
			public:
				virtual const char* what() const throw()
				{
					return ("Error: Index out of bounds");
				}
		};
};

#endif
