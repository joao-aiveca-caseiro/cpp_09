/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:19:09 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/11/15 18:21:45 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

class BitcoinExchange
{

	public:

		~BitcoinExchange();
		static	void	createDatabase();
		static	void	createInputList();

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

#endif