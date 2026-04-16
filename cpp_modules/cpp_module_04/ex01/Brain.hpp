#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		~Brain();
		Brain(const Brain &other);
		Brain &operator=(const Brain &other);
		const std::string getIdea(int index) const;
		void setIdea(int index, const std::string &idea);
		const std::string getFirstIdea() const;
};

#endif