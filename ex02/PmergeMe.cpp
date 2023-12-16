/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/16 02:42:27 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::vector<int> PmergeMe::_vector;
std::list<int> PmergeMe::_list;

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &target)
{
	*this = target;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &target)
{
	(void)target;
	return *this;
}

void	PmergeMe::validateInput(char **arg)
{
	int i = 0;
	while (arg[++i])
	{
		std::string str(arg[i]);
		if (str.find_first_not_of("0123456789") != std::string::npos
		|| std::atol(arg[i]) > std::numeric_limits<int>::max())
		{
			std::cout << "HEREEE" << std::endl;
			throw InvalidExpression();
		}
		_vector.push_back(std::atoi(arg[i]));
		_list.push_back(std::atoi(arg[i]));
	}
	checkIfSorted();
}

void	PmergeMe::initSorting()
{
	std::cout << "Before sorting: ";
	printSequence();
	
	clock_t vecStartTime = clock();
	vectorSorting();
	clock_t vecEndTime = clock();
	
	// clock_t lstStartTime = clock();
	// listSorting();
	// clock_t lstEndTime = clock();

	// std::cout << "After sorting: ";
	// printSequence();
	 std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << ((double)(vecEndTime - vecStartTime)) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
	// std::cout << "Time to process a range of " << _vector.size() << " elements with std::list: " << ((double)(lstEndTime - lstStartTime)) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

void	PmergeMe::printSequence()
{
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::checkIfSorted()
{
	std::vector<int>::iterator it;
	for (it = _vector.begin(); it != _vector.end(); it++)
	{
		if (it != _vector.begin())
			if (*it < *(it - 1))
				break;
	}
	if (it == _vector.end())
		throw AlreadySorted();
}

void	PmergeMe::vectorSorting()
{
	int unpaired = -1;
	// divide sequence into pairs, first element is the lower one in each pair
	std::vector<std::pair<int, int> > vecPairs;
	for (std::vector<int>::iterator it =_vector.begin(); it !=_vector.end(); )
	{
		if (it == _vector.begin())
		{
			if (_vector.size() % 2 != 0)
				unpaired = *it;
			it++;
		}
		else if (it != _vector.begin())
		{
			vecPairs.push_back(std::make_pair(std::min(*it, *(it - 1)), std::max(*it, *(it - 1))));
			it++;
			if (it != _vector.end())
				it++;
		}
	}
	// order the second (highest) elements of each pair using mergesort
	vecPairs = vectorMergeSort(vecPairs);
	// std::cout << "VECPAIRS TOP ELEMENTS " << std::endl;
	// for (std::vector<std::pair<int, int> >::iterator it2 = vecPairs.begin(); it2 != vecPairs.end(); it2++)
	// {
	// 	std::cout << it2->second << " " << std::endl;
	// }
	// _vector.push_back(unpaired);
	
	
}

std::vector<std::pair<int, int> > PmergeMe::vectorMergeSort(std::vector<std::pair<int, int> > vecPairs)
{
	size_t i = 0;
	std::vector<std::pair<int, int> > v1, v2;
	
	if (vecPairs.size() <= 1)
		return vecPairs;
	
	for (std::vector<std::pair<int, int> >::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
	{
		if (i++ < vecPairs.size() / 2)	
			v1.push_back(*it);
		else
			v2.push_back(*it);
		std::cout << it->second << " ";
	}
	std::cout << std::endl;
	v1 = vectorMergeSort(v1);
	v2 = vectorMergeSort(v2);
	return mergeVectors(v1, v2);
}

std::vector<std::pair<int, int> > PmergeMe::mergeVectors(std::vector<std::pair<int, int> > v1, std::vector<std::pair<int, int> > v2)
{
	std::vector<std::pair<int, int> > res;
	while (!v1.empty() && !v2.empty())
	{
		if (v1.front().second <= v2.front().second)
		{
			res.push_back(v1.front());
			v1.erase(v1.begin());
		}
		else
		{
			res.push_back(v2.front());
			v2.erase(v2.begin());
		}
	}
	// one of the vecs may still have elements
	res.insert(res.end(), v1.begin(), v1.end());
    res.insert(res.end(), v2.begin(), v2.end());
	return res;
}