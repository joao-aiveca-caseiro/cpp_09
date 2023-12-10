/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:19:09 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/08 14:43:09 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

class PmergeMe
{

	public:

		~PmergeMe();
		static void	validateInput(std::string arg);
		static long	calculateExpression(std::string arg);
		

	private:

		PmergeMe();
		PmergeMe(const PmergeMe &target);
		PmergeMe &operator=(const PmergeMe &target);

};

class InvalidExpression: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: please provide a sequence of more than one positive integer as argument.");
	}
};

class InvalidToken: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: invalid token. The operands must be single digits, and the operators '*', '/', '+' or '-'");
	}
};

#endif