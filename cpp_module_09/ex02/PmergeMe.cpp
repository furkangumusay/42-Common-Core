#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vectorData = other._vectorData;
		this->_dequeData = other._dequeData;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		
		for (size_t j = 0; j < arg.length(); j++)
		{
			if (!isdigit(arg[j]))
			{
				std::cerr << "Error" << std::endl;
				return (false);
			}
		}
		
		long num = atol(arg.c_str());
		if (num < 0 || num > 2147483647)
		{
			std::cerr << "Error" << std::endl;
			return (false);
		}
		
		_vectorData.push_back(static_cast<int>(num));
		_dequeData.push_back(static_cast<int>(num));
	}
	
	if (_vectorData.empty())
	{
		std::cerr << "Error" << std::endl;
		return (false);
	}
	
	return (true);
}

size_t PmergeMe::jacobsthal(size_t n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	
	size_t prev2 = 0;
	size_t prev1 = 1;
	size_t result = 0;
	
	for (size_t i = 2; i <= n; ++i)
	{
		result = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = result;
	}
	return result;
}

std::vector<size_t> PmergeMe::buildJacobsthalSequence(size_t size)
{
	std::vector<size_t> sequence;
	if (size == 0) return sequence;
	
	std::vector<size_t> jacobsthalNums;
	size_t idx = 0;
	while (jacobsthal(idx) < size)
	{
		jacobsthalNums.push_back(jacobsthal(idx));
		++idx;
	}
	jacobsthalNums.push_back(jacobsthal(idx));
	
	std::vector<bool> used(size, false);
	
	for (size_t i = 1; i < jacobsthalNums.size(); ++i)
	{
		size_t curr = jacobsthalNums[i];
		size_t prev = jacobsthalNums[i - 1];
		
		for (size_t j = std::min(curr, size); j > prev; --j)
		{
			if (j > 0 && j <= size && !used[j - 1])
			{
				sequence.push_back(j - 1);
				used[j - 1] = true;
			}
		}
	}
	
	for (size_t i = 0; i < size; ++i)
	{
		if (!used[i])
			sequence.push_back(i);
	}
	
	return sequence;
}

void PmergeMe::binaryInsertVector(std::vector<int>& mainChain, int element, size_t end)
{
	size_t left = 0;
	size_t right = end;
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (mainChain[mid] > element)
			right = mid;
		else
			left = mid + 1;
	}
	mainChain.insert(mainChain.begin() + static_cast<long>(left), element);
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1) return;
	
	std::vector<std::pair<int, int> > pairs;
	bool hasStraggler = (n % 2 == 1);
	int straggler = 0;
	
	if (hasStraggler)
		straggler = arr[n - 1];
	
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}
	
	if (pairs.size() > 1)
	{
		std::vector<int> winners;
		for (size_t i = 0; i < pairs.size(); ++i)
			winners.push_back(pairs[i].first);
		
		fordJohnsonVector(winners);
		
		std::vector<std::pair<int, int> > sortedPairs;
		for (size_t i = 0; i < winners.size(); ++i)
		{
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				if (pairs[j].first == winners[i])
				{
					sortedPairs.push_back(pairs[j]);
					pairs.erase(pairs.begin() + static_cast<long>(j));
					break;
				}
			}
		}
		pairs = sortedPairs;
	}
	
	std::vector<int> mainChain;
	for (size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].first);
	
	if (!pairs.empty())
		mainChain.insert(mainChain.begin(), pairs[0].second);
	
	if (pairs.size() > 1)
	{
		std::vector<int> pend;
		for (size_t i = 1; i < pairs.size(); ++i)
			pend.push_back(pairs[i].second);
		
		std::vector<size_t> insertOrder = buildJacobsthalSequence(pend.size());
		
		for (size_t i = 0; i < insertOrder.size(); ++i)
		{
			size_t idx = insertOrder[i];
			if (idx < pend.size())
			{
				size_t bound = mainChain.size();
				for (size_t j = 0; j < mainChain.size(); ++j)
				{
					if (mainChain[j] == pairs[idx + 1].first)
					{
						bound = j;
						break;
					}
				}
				binaryInsertVector(mainChain, pend[idx], bound);
			}
		}
	}
	
	if (hasStraggler)
		binaryInsertVector(mainChain, straggler, mainChain.size());
	
	arr = mainChain;
}

void PmergeMe::binaryInsertDeque(std::deque<int>& mainChain, int element, size_t end)
{
	size_t left = 0;
	size_t right = end;
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (mainChain[mid] > element)
			right = mid;
		else
			left = mid + 1;
	}
	mainChain.insert(mainChain.begin() + static_cast<long>(left), element);
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1) return;
	
	std::deque<std::pair<int, int> > pairs;
	bool hasStraggler = (n % 2 == 1);
	int straggler = 0;
	
	if (hasStraggler)
		straggler = arr[n - 1];
	
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}
	
	if (pairs.size() > 1)
	{
		std::deque<int> winners;
		for (size_t i = 0; i < pairs.size(); ++i)
			winners.push_back(pairs[i].first);
		
		fordJohnsonDeque(winners);
		
		std::deque<std::pair<int, int> > sortedPairs;
		for (size_t i = 0; i < winners.size(); ++i)
		{
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				if (pairs[j].first == winners[i])
				{
					sortedPairs.push_back(pairs[j]);
					pairs.erase(pairs.begin() + static_cast<long>(j));
					break;
				}
			}
		}
		pairs = sortedPairs;
	}
	
	std::deque<int> mainChain;
	for (size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].first);
	
	if (!pairs.empty())
		mainChain.insert(mainChain.begin(), pairs[0].second);
	
	if (pairs.size() > 1)
	{
		std::deque<int> pend;
		for (size_t i = 1; i < pairs.size(); ++i)
			pend.push_back(pairs[i].second);
		
		std::vector<size_t> insertOrder = buildJacobsthalSequence(pend.size());
		
		for (size_t i = 0; i < insertOrder.size(); ++i)
		{
			size_t idx = insertOrder[i];
			if (idx < pend.size())
			{
				size_t bound = mainChain.size();
				for (size_t j = 0; j < mainChain.size(); ++j)
				{
					if (mainChain[j] == pairs[idx + 1].first)
					{
						bound = j;
						break;
					}
				}
				binaryInsertDeque(mainChain, pend[idx], bound);
			}
		}
	}
	
	if (hasStraggler)
		binaryInsertDeque(mainChain, straggler, mainChain.size());
	
	arr = mainChain;
}

void PmergeMe::sort()
{
	clock_t start = clock();
	fordJohnsonVector(_vectorData);
	clock_t end = clock();
	double vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
	start = clock();
	fordJohnsonDeque(_dequeData);
	end = clock();
	double dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
	std::cout << "Time to process a range of " << _vectorData.size() 
	          << " elements with std::vector : " << std::fixed << std::setprecision(5) 
	          << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _dequeData.size() 
	          << " elements with std::deque  : " << std::fixed << std::setprecision(5) 
	          << dequeTime << " us" << std::endl;
}

void PmergeMe::printBefore() const
{
	std::cout << "Before:";
	for (size_t i = 0; i < _vectorData.size(); i++)
		std::cout << " " << _vectorData[i];
	std::cout << std::endl;
}

void PmergeMe::printAfter() const
{
	std::cout << "After:";
	for (size_t i = 0; i < _vectorData.size(); i++)
		std::cout << " " << _vectorData[i];
	std::cout << std::endl;
}
