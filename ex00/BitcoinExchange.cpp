/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/11/15 18:25:17 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &target)
{
	*this = target;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &target)
{
	(void)target;
	return *this;
}

void	BitcoinExchange::createDatabase()
{
	std::ifstream	ifstrm("data.csv");
	std::string		line;
	
	if (!ifstrm.is_open())
		throw ErrorLoadingDatabase();
	while (std::getline(ifstrm, line))
	{
		int	comma = line.find(',');
		std::string date = line.substr(0, comma);
		float		value = atof((line.substr(comma)).c_str());
		_database[date] = value;
	}
	
	ifstrm.close();
}