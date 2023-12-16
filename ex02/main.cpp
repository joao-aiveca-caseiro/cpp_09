/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:18:31 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/13 18:18:09 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc <= 2)
			throw InvalidExpression();
		PmergeMe::validateInput(argv);
		PmergeMe::initSorting();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
}