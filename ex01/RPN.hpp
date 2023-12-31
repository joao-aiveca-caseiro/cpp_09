/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:19:09 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/17 02:09:28 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stack>

class RPN
{

	public:

		~RPN();
		static void	validateInput(std::string arg);
		static long	calculateExpression(std::string arg);
		

	private:

		RPN();
		RPN(const RPN &target);
		RPN &operator=(const RPN &target);
		static std::stack<long> _stack;

};

class InvalidExpression: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: please provide a single valid RPN expression as argument.");
	}
};

class InvalidToken: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: invalid token. The operands must be single digits, and the operators '*', '/', '+' or '-'");
	}
};

class DivideByZero: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: Undefined behaviour due to a division by 0");
	}
};

#endif