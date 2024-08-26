
#include "BitcoinExchange.hpp"
#include <iostream>

// Constructors 

BitcoinExchange::BitcoinExchange(void) {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	(void)src;
}

BitcoinExchange &BitcoinExchange::operator = (const BitcoinExchange &src) {
	(void)src;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {

}

// Class functions 

void BitcoinExchange::parse(char *argv) {

	std::fstream file;
	file.open(argv, std::fstream::in);

	if (file.is_open())
		checkFileFormatting(file);	
	else 
		throw std::runtime_error("Could not open file for reading!");
}
