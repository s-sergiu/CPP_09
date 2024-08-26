
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
		this->checkFileFormatting(file);	
	else 
		throw std::runtime_error("Could not open file for reading!");
}

void BitcoinExchange::checkFileFormatting(std::fstream &file) const {

	std::string str;

	checkFileHeader(file);
	while(std::getline(file, str))
			checkFileValues(str);
}

void BitcoinExchange::checkFileHeader(std::fstream &file) const {
	std::string str;
	file >> str;
	if (str != "date")
		throw std::runtime_error("Incorrect header format for input file");
	file >> str;
	if (str != "|")
		throw std::runtime_error("Incorrect header format for input file");
	file >> str;
	if (str != "value")
		throw std::runtime_error("Incorrect header format for input file");
}

void BitcoinExchange::checkFileValues(std::string &str) const {
	if (!str.empty())
		std::cout<<"line: "<<str<<std::endl;
}
