/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:18:31 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/08 14:47:16 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc <= 2)
			throw InvalidExpression();	
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
}