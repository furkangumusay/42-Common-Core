#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <utility>

class PmergeMe
{
	private:
		std::vector<int> _vectorData;
		std::deque<int> _dequeData;
		
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		
		// Jacobsthal sequence helper
		static size_t jacobsthal(size_t n);
		static std::vector<size_t> buildJacobsthalSequence(size_t size);
		
		// Ford-Johnson algorithm for vector
		void fordJohnsonVector(std::vector<int>& arr);
		void binaryInsertVector(std::vector<int>& mainChain, int element, size_t end);
		
		// Ford-Johnson algorithm for deque
		void fordJohnsonDeque(std::deque<int>& arr);
		void binaryInsertDeque(std::deque<int>& mainChain, int element, size_t end);
	
	public:
		PmergeMe();
		~PmergeMe();
		
		bool parseInput(int argc, char** argv);
		void sort();
		void printBefore() const;
		void printAfter() const;
};

#endif
