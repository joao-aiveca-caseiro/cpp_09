/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/11/30 14:40:06 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

	std::map<std::string, float> BitcoinExchange::_database;
	std::map<std::string, float> BitcoinExchange::_inputlist;

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
	std::ifstream	file("data.csv");
	std::string		line;
	
	if (!file.is_open())
		throw ErrorLoadingDatabase();
	std::getline(file, line); // skip first line
	while (std::getline(file, line))
	{
		int	comma = line.find(',');
		std::string date = line.substr(0, comma);
		float		value = atof((line.substr(comma)).c_str());
		_database[date] = value;
	}
	
	file.close();
}

void	BitcoinExchange::createInputList(char *filename)
{
	std::ifstream	file(filename);
	std::string		line;
	
	if (!file.is_open())
		throw ErrorLoadingInput();
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string token;
		iss >> token;
		if (!checkValidDate(token))
			std::cout << "Error: Invalid date => " << token << std::endl;

	}
	
}

bool	BitcoinExchange::checkValidDate(std::string date)
{
	if (date.size() != 10 && date[4] != '-' && date[7] != '-' && date.find_first_not_of("0123456789-") != std::string::npos)
		return false;
	std::string	year = date.substr(0, 4);
	std::string	month = date.substr(5, 2);
	std::string day = date.substr(8);
	std::cout << year << "|" << month << "|" << day << std::endl;
	if (std::atoi(year.c_str()) < 2009)
		return false;
	if (std::atoi(year.c_str()) < 1 && std::atoi(year.c_str()))
		return false; 
	return true;
}

void	BitcoinExchange::printValues()
{
	std::map<std::string, float>::iterator it;
	
	std::cout << "DATABASE" << std::endl;
	for (it = _database.begin(); it != _database.end(); it++)
	{
		std::cout << it->first << "," << it->second << std::endl;
	}
	std::cout << "\nINPUT FILE" << std::endl;
	for (it = _inputlist.begin(); it != _inputlist.end(); it++)
	{
		std::cout << it->first << " | " << it->second << std::endl;
	}	
}