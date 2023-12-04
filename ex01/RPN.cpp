/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/04 15:52:18 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<long> RPN::_stack;

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &target)
{
	*this = target;
}

RPN &RPN::operator=(const RPN &target)
{
	(void)target;
	return *this;
}

void	RPN::validateInput(std::string arg)
{
	if (arg.find_first_not_of("0123456789-+/* ") != std::string::npos)
		throw InvalidExpression();
}

long	RPN::calculateExpression(std::string arg)
{
	std::istringstream iss(arg);
	std::string token;
	bool		has_operand;

	while (iss >> token)
	{
		// is operand 1 -1 12
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