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
	printSequence(1);
	
	clock_t vecStartTime = clock();
	vectorSorting();
	clock_t vecEndTime = clock();
	
	clock_t lstStartTime = clock();
	listSorting();
	clock_t lstEndTime = clock();

	std::cout << "After sorting: ";
	printSequence(1);
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << ((double)(vecEndTime - vecStartTime)) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::list: " << ((double)(lstEndTime - lstStartTime)) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

void	PmergeMe::printSequence(int flag)
{
	if (flag == 0)
	{
		for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
		{
			std::cout << *it << " ";
		}
	}
	else
	{
		for (std::list<int>::iterator it = _list.begin(); it != _list.end(); it++)
		{
			std::cout << *it << " ";
		}		
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
			{
				unpaired = *it;
				it++;
			}
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
	
	// Add the now ordered highest elements of each pair to the final vector
	std::vector<int> res;
	for (std::vector<std::pair<int, int> >::iterator it2 = vecPairs.begin(); it2 != vecPairs.end(); it2++)
	{
		res.push_back(it2->second);
	}
	// Insert the first element of the first (smallest) pair on the final vector
	res.insert(res.begin(), vecPairs.front().first);
	vecPairs.erase(vecPairs.begin());
	
	//Use binary search to insert the remaining elements on the correct position
	if (unpaired != -1)
		res.insert(vecBinarySearch(unpaired, res), unpaired);
	while(!vecPairs.empty())
	{
		res.insert(vecBinarySearch(vecPairs.front().first, res), vecPairs.front().first);
		vecPairs.erase(vecPairs.begin());
	}
	_vector = res;
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
	}
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

std::vector<int>::iterator PmergeMe::vecBinarySearch(int num, std::vector<int> &vec)
{
	std::vector<int>::iterator l_bound = vec.begin();
	std::vector<int>::iterator r_bound = vec.end();
	while (l_bound != r_bound)
	{
		std::vector<int>::iterator midpoint = l_bound;
		std::advance(midpoint, std::distance(l_bound, r_bound) / 2);
		if (num == *midpoint)
			return midpoint;
		else if (num > *midpoint)
			l_bound = ++midpoint;
		else
			r_bound = midpoint;
	}
	return l_bound;
}

///////////////////////////////////////////
///////////// LIST ////////////////////////
///////////////////////////////////////////

void	PmergeMe::listSorting()
{
	int unpaired = -1;
	// divide sequence into pairs, first element is the lower one in each pair
	std::list<std::pair<int, int> > lstPairs;
	std::list<int>::iterator prev = _list.begin();
	for (std::list<int>::iterator it =_list.begin(); it !=_list.end(); )
	{
		if (it == _list.begin())
		{
			if (_list.size() % 2 != 0)
			{
				unpaired = *it;
				it++;
			}
			prev = it;
			it++;
		}
		else if (it != _list.begin())
		{
			lstPairs.push_back(std::make_pair(std::min(*it, *prev), std::max(*it, *prev)));
			prev = it;
			it++;
			if (it != _list.end())
			{
				prev = it;
				it++;
			}
		}
	}
	// order the second (highest) elements of each pair using mergesort
	lstPairs = listMergeSort(lstPairs);
	
	// Add the now ordered highest elements of each pair to the final list
	std::list<int> res;
	for (std::list<std::pair<int, int> >::iterator it2 = lstPairs.begin(); it2 != lstPairs.end(); it2++)
	{
		res.push_back(it2->second);
	}
	// Insert the first element of the first (smallest) pair on the final list
	res.insert(res.begin(), lstPairs.front().first);
	lstPairs.erase(lstPairs.begin());
	
	//Use binary search to insert the remaining elements on the correct position
	if (unpaired != -1)
		res.insert(lstBinarySearch(unpaired, res), unpaired);
	while(!lstPairs.empty())
	{
		res.insert(lstBinarySearch(lstPairs.front().first, res), lstPairs.front().first);
		lstPairs.erase(lstPairs.begin());
	}
	_list = res;
}

std::list<std::pair<int, int> > PmergeMe::listMergeSort(std::list<std::pair<int, int> > lstPairs)
{
	size_t i = 0;
	std::list<std::pair<int, int> > v1, v2;
	
	if (lstPairs.size() <= 1)
		return lstPairs;
	
	for (std::list<std::pair<int, int> >::iterator it = lstPairs.begin(); it != lstPairs.end(); it++)
	{
		if (i++ < lstPairs.size() / 2)	
			v1.push_back(*it);
		else
			v2.push_back(*it);
	}
	v1 = listMergeSort(v1);
	v2 = listMergeSort(v2);
	return mergeLists(v1, v2);
}

std::list<std::pair<int, int> > PmergeMe::mergeLists(std::list<std::pair<int, int> > v1, std::list<std::pair<int, int> > v2)
{
	std::list<std::pair<int, int> > res;
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
	// one of the lsts may still have elements
	res.insert(res.end(), v1.begin(), v1.end());
    res.insert(res.end(), v2.begin(), v2.end());
	return res;
}

std::list<int>::iterator PmergeMe::lstBinarySearch(int num, std::list<int> &lst)
{
	std::list<int>::iterator l_bound = lst.begin();
	std::list<int>::iterator r_bound = lst.end();
	while (l_bound != r_bound)
	{
		std::list<int>::iterator midpoint = l_bound;
		std::advance(midpoint, std::distance(l_bound, r_bound) / 2);
		if (num == *midpoint)
			return midpoint;
		else if (num > *midpoint)
			l_bound = ++midpoint;
		else
			r_bound = midpoint;
	}
	return l_bound;
}