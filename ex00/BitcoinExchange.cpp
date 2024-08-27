
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
	std::string chunk;
	struct tm tp;

	if (!str.empty()) {
		chunk = str.substr(0, str.find('|'));
		strptime(&chunk[0] ,"%Y-%m-%d", &tp);
		tp.tm_year += 1900;
		tp.tm_mday += 1;
		std::cout<<chunk<<std::endl;
		std::cout<<"year: "<<tp.tm_year<<std::endl;
		std::cout<<"mon: "<<tp.tm_mon<<std::endl;
		std::cout<<"day: "<<tp.tm_mday<<std::endl;
		checkYear(tp);
		checkMonth(tp);
		checkDay(tp);
	}

}

void BitcoinExchange::checkMonth(struct tm &tp) const {
	if (tp.tm_mon < 1 || tp.tm_mon > 12)
		throw std::runtime_error("Incorrect month!");
}

void BitcoinExchange::checkDay(struct tm &tp) const {
	if (tp.tm_mday < 1 || tp.tm_mday > 31)
		throw std::runtime_error("Incorrect day!");
}

void BitcoinExchange::checkYear(struct tm &tp) const {
	if (tp.tm_year < 1900 || tp.tm_year > 2024)
		throw std::runtime_error("Incorrect year!");
}
