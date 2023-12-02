/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/02 02:58:48 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<time_t, float>	BitcoinExchange::_database;
time_t					BitcoinExchange::_time;
float					BitcoinExchange::_balance;

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
		std::tm	timeinfo;
		
		int	year = std::atoi((line.substr(0, 4)).c_str());
		int	month = std::atoi((line.substr(5, 2)).c_str());
		int day = std::atoi((line.substr(8, 2)).c_str());
		timeinfo.tm_mday = day;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_year = year - 1900;
		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec = 0;
		timeinfo.tm_isdst = -1;
		time_t		date = mktime(&timeinfo);
		float		value = atof((line.substr(11)).c_str());
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
		std::string date, separator, value;
		// if (iss >> token && !checkValidDate(token))
		// 	std::cout << "Error: Invalid date => " << token << std::endl;
		// if (iss >> token && token != "|")
		// 	std::cout << "Error: Invalid syntax => " << token << std::endl;
		// if (iss >> token && !checkValidBalance(token))
		// 	std::cout << "Error: Invalid balance => " << token << std::endl;
		// if (iss >> token)
		// 	std::cout << "Error: Invalid syntax => " << token << std::endl;
		// else
		// 	convertToFiat()
		iss >> date >> separator >> value;
		if (!checkValidDate(date))
		{
			std::cout << "Error: Invalid date => " << date << std::endl;
			continue;
		}
		if (separator != "|")
		{
			std::cout << "Error: Invalid syntax => " << separator << std::endl;
			continue;
		}
		if (!checkValidBalance(value))
		{
			std::cout << "Error: Invalid balance => " << value << std::endl;
			continue;
		}
		if (iss.peek() != EOF)
			std::cout << "Error: Invalid syntax. Too many elements" << std::endl;
	}
	
}

bool	BitcoinExchange::checkValidDate(std::string date)
{
	std::tm		timeinfo;
	int			max_days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (date.size() != 10 && date[4] != '-' && date[7] != '-' && date.find_first_not_of("0123456789-") != std::string::npos)
		return false;
	int	year = std::atoi((date.substr(0, 4)).c_str());
	int	month = std::atoi((date.substr(5, 2)).c_str());
	int day = std::atoi((date.substr(8)).c_str());
	if (year < 2009)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > max_days[day] || (day == 29 && month == 2 && year % 4 != 0))
		return false;
	timeinfo.tm_mday = day;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_year = year - 1900;
	timeinfo.tm_hour = 0;
	timeinfo.tm_min = 0;
	timeinfo.tm_sec = 0;
	timeinfo.tm_isdst = -1;
	_time = mktime(&timeinfo);
	if (_time > std::time(NULL))
		return false;
	return true;
}

bool	BitcoinExchange::checkValidBalance(std::string balance)
{
	if (balance.find_first_not_of("0123456789.") != std::string::npos)
		return false;
	_balance = atof(balance.c_str());
	if (_balance < 0 || _balance > 1000)
		return false;
	return true;
}

void	BitcoinExchange::printValues()
{
	std::map<time_t, float>::iterator it;
	
	std::cout << "DATABASE" << std::endl;
	for (it = _database.begin(); it != _database.end(); it++)
	{
		std::cout << it->first << "," << it->second << std::endl;
	}
}