
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
	while(std::getline(file, str)) {
		checkDateValues(str);
		checkNumericValues(str);
	}
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

void BitcoinExchange::checkDateValues(std::string &str) const {
	std::string chunk;
	struct tm tp;

	if (!str.empty()) {
		chunk = str.substr(0, str.find('|'));
		strptime(&chunk[0] ,"%Y-%m-%d", &tp);
		convertReadableTime(&tp);
		checkYear(tp,chunk);
		checkMonth(tp,chunk);
		checkDay(tp,chunk);
	}

}

void BitcoinExchange::checkNumericValues(std::string &str) const {
	std::string chunk;
	char *test = NULL;
	double number;

	if (!str.empty()) {
		chunk = str.substr(str.find('|') + 1, str.size());
		number = std::strtod(chunk.c_str(), &test);
		if (number > 1000)
			std::cerr<<"Error: too large a number."<<std::endl;
		if (number < 0)
			std::cerr<<"Error: not a positive number."<<std::endl;
	}

}

void BitcoinExchange::checkMonth(struct tm &tp, std::string &str) const {
	if (tp.tm_mon < 1 || tp.tm_mon > 12)
		std::cerr<<"Error: bad input => "<<str<<std::endl;
}

void BitcoinExchange::checkDay(struct tm &tp, std::string &str) const {
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ((tp.tm_year % 4 == 0 && tp.tm_year % 100 != 0) || (tp.tm_year % 400 == 0))
		monthDays[1] = 29;
	if (tp.tm_mday < 1 || tp.tm_mday > monthDays[tp.tm_mon - 1])
		std::cerr<<"Error: bad input => "<<str<<std::endl;
}

void BitcoinExchange::checkYear(struct tm &tp, std::string &str) const {
	if (tp.tm_year < 1900 || tp.tm_year > 2024)
		std::cerr<<"Error: bad input => "<<str<<std::endl;
}

void BitcoinExchange::convertReadableTime(struct tm *tp) const {
		tp->tm_year += 1900;
		tp->tm_mday += 0;
		tp->tm_mon += 1;
}
