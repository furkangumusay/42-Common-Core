#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <exception>
# include <limits>

class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;

		Span();

	public:
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int number);
		
		template <typename IT>
		void addNumber(IT begin, IT end)
		{
			if (std::distance(begin, end) + _numbers.size() > _maxSize)
				throw SpanFullException();
			_numbers.insert(_numbers.end(), begin, end);
		}

		int shortestSpan() const;
		int longestSpan() const;

		unsigned int size() const;
		unsigned int capacity() const;

		class SpanFullException : public std::exception
		{
			public:
				virtual const char* what() const throw() {
					return ("Span is full, cannot add more numbers");
				}
		};

		class NotEnoughElementsException : public std::exception
		{
			public:
				virtual const char* what() const throw() {
					return ("Not enough elements to calculate span");
				}
		};
};

#endif
