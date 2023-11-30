/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:19:09 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/11/30 13:14:16 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

class BitcoinExchange
{

	public:

		~BitcoinExchange();
		static	void	createDatabase();
		static	void	createInputList(char *filename);
		static	void	printValues();
		static 	bool	checkValidDate(std::string date);

	private:

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &target);
		BitcoinExchange &operator=(const BitcoinExchange &target);
		static	std::map<std::string, float> _database;
		static	std::map<std::string, float> _inputlist;

};

class ErrorLoadingDatabase: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: could not open database file.");
	}
};

class InvalidNumberArguments: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: please provide a single file as argument.");
	}
};

class ErrorLoadingInput: public std::exception
{
	virtual const char* what() const throw()
	{
		return ("Error: could not open input file.");
	}
};

#endif