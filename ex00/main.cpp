/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:18:31 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/02 02:43:23 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw InvalidNumberArguments();	
		BitcoinExchange::createDatabase();
		BitcoinExchange::createInputList(argv[1]);
		//BitcoinExchange::printValues();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}