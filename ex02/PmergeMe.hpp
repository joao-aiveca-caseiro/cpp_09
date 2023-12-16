/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:19:09 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/16 01:42:30 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <list>
#include <limits>
#include <ctime>

class PmergeMe
{

	public:

		~PmergeMe();
		static void	validateInput(char **arg);
		static void	initSorting();
		static void printSequence();
		static void checkIfSorted();
		static void vectorSorting();
		static std::vector<std::pair<int, int> > vectorMergeSort(std::vector<std::pair<int, int> > vecPairs);
		static std::vector<std::pair<int, int> > mergeVectors(std::vector<std::pair<int, int> > v1, std::vector<std::pair<int, int> > v2);
		static void listSorting();

	private:

		PmergeMe();
		PmergeMe(const PmergeMe &target);
		PmergeMe &operator=(const PmergeMe &target);
		static std::vector<int> _vector;
		static std::list<int> _list;

};

class InvalidExpression: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: please provide a sequence of more than one positive integer as argument.");
	}
};

class AlreadySorted: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: the provided sequence is already sorted.");
	}
};

#endif