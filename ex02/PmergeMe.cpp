/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/08 14:46:58 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::stack<long> PmergeMe::_stack;

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

void	PmergeMe::validateInput(std::string arg)
{
	if (arg.find_first_not_of("0123456789-+/* ") != std::string::npos)
		throw InvalidExpression();
}

long	PmergeMe::calculateExpression(std::string arg)
{
	std::istringstream iss(arg);
	std::string token;
	bool		has_operand;

	while (iss >> token)
	{
		// is operand
		if ((isdigit(token[0]) && token.size() == 1) || (token.size() == 2 && token[0] == '-' && isdigit(token[1])))
			_stack.push(std::atol(token.c_str()));
		// is operator
		else if (token.size() == 1 && token.find_first_not_of("-+/*") == std::string::npos)
		{
			has_operand = true;
			if (_stack.size() < 2)
				throw InvalidExpression();
			long	r_operand = _stack.top();
			_stack.pop();
			long	l_operand = _stack.top();
			_stack.pop();
			if (token == "+")
				_stack.push(l_operand + r_operand);
			else if (token == "-")
				_stack.push(l_operand - r_operand);
			else if (token == "*")
				_stack.push(l_operand * r_operand);
			else if (token == "/")
				_stack.push(l_operand / r_operand);
		}
		// is invalid
		else
			throw InvalidToken();
	}
	if (!has_operand || _stack.size() != 1)
		throw InvalidExpression();
	return _stack.top();
}