/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:18:49 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/12/03 01:25:39 by jaiveca-         ###   ########.fr       */
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
	bool			firstline = true;
	
	if (!file.is_open())
		throw ErrorLoadingInput();
	while (std::getline(file, line))
	{
		if (firstline && line == "date | value")
		{
			firstline = false;
			continue;
		}
		std::istringstream iss(line);
		std::string date, separator, value;
		iss >> date >> separator >> value;
		if (date.empty() || separator.empty() || value.empty() || iss.peek() != EOF)
			std::cout << "Error: Invalid syntax => " << line << std::endl;
		else if (!checkValidDate(date))
			std::cout << "Error: Invalid date => " << date << std::endl;
		else if (separator != "|")
			std::cout << "Error: Invalid separator => " << separator << std::endl;
		else if (!checkValidBalance(value))
			std::cout << "Error: Invalid balance => " << value << std::endl;
		else
			convertToFiat(date, value);
	}
}

bool	BitcoinExchange::checkValidDate(std::string date)
{
	std::tm		timeinfo;
	int			max_days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (date.size() != 10 || date.find_first_not_of("0123456789-") != std::string::npos
	|| date[4] != '-' || date[7] != '-' || date[6] == '-' || date[9] == '-')
		return false;
	int	year = std::atoi((date.substr(0, 4)).c_str());
	int	month = std::atoi((date.substr(5, 2)).c_str());
	int day = std::atoi((date.substr(8)).c_str());
	if (year < 2009)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > max_days[month] || (day == 29 && month == 2 && year % 4 != 0) || (day == 1 && month == 1 && year == 2009))
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

void	BitcoinExchange::convertToFiat(std::string date, std::string value)
{
	size_t	min_difference = std::string::npos;
	float	selected_rate = -1;
	for (std::map<time_t, float>::iterator it = _database.begin(); it != _database.end(); it++)
	{
		if (it->first <= _time)
		{
			size_t difference = _time - it->first;
			if (difference < min_difference)
			{
				min_difference = difference;
				selected_rate = it->second;
			}
		}
	}
	std::cout << date << " => " << value << " = " << _balance * selected_rate << std::endl;
}

bool	BitcoinExchange::checkValidBalance(std::string balance)
{
	if (balance.find_first_not_of("0123456789.") != std::string::npos || balance.find('.') != balance.rfind('.'))
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