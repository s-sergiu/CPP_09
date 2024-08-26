
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

void BitcoinExchange::parse(char **argv) {
	(void)argv;
	std::fstream file;
	file.open(argv[1], std::fstream::in);
	std::cout<<argv[1]<<std::endl;
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file for reading!");
	}
	else {
		std::cout<<"file open"<<std::endl;
		std::cout<<"file contents: "<<file.rdbuf();
		file.close();
	}
}
