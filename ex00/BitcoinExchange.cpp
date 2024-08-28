
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

void BitcoinExchange::loadCSVToData(std::fstream &file) {
	std::string str, str_value;
	double value;

	checkCSVHeader(file);
	while(std::getline(file, str)) {
		str_value = str.substr(str.find(',') + 1 , str.size());
		value = std::strtof(&str_value[0], NULL);
		this->data[str.substr(0, str.find(','))] = value;
	}
}

void BitcoinExchange::checkFileFormatting(std::fstream &file) {
	std::string str;
	int flag = 0;

	checkFileHeader(file);
	while(std::getline(file, str)) {
		checkDateValues(str,flag);
		if (!flag)
			checkNumericValues(str);
		flag = 0;
	}
}

void BitcoinExchange::checkCSVHeader(std::fstream &file) const {
	std::string str;
	file >> str;
	if (str != "date,exchange_rate")
		throw std::runtime_error("Incorrect header format for csv file");
}

void BitcoinExchange::checkFileHeader(std::fstream &file) const {
	std::string str;
	file >> str;
	if (str == "date,exchange_rate")
		return ;
	if (str != "date")
		throw std::runtime_error("Incorrect header format for input file");
	file >> str;
	if (str != "|")
		throw std::runtime_error("Incorrect header format for input file");
	file >> str;
	if (str != "value")
		throw std::runtime_error("Incorrect header format for input file");
}

void BitcoinExchange::checkDateValues(std::string &str, int &flag) const {
	std::string chunk;
	double date[3];

	if (!str.empty()) {
		chunk = str.substr(0, str.find('|'));
		converDateToDouble(date, chunk);
		checkYear(date, flag);
		if (!flag)
			checkMonth(date, flag);
		if (!flag)
			checkDay(date, flag);
	}

}

void BitcoinExchange::checkNumericValues(std::string &str) {
	std::string chunk, date;
	char *test = NULL;
	double number;
	char buffer[11];
	std::map<std::string, double>::iterator it;

	if (!str.empty()) {
		date = str.substr(0 , str.find('|'));
		chunk = str.substr(str.find('|') + 1, str.size());
		number = std::strtod(chunk.c_str(), &test);
		if (number > 1000) {
			std::cerr<<"Error: too large a number."<<std::endl;
			return ;
		}
		if (number < 0) {
			std::cerr<<"Error: not a positive number."<<std::endl;
			return ;
		}
		date.copy(buffer,10, 0);
		(void)data[buffer];
		it = data.find(buffer);
		while (it->second == 0)
			it--;
		double rate = number * it->second;
		std::cout<<date<<"=> "<<number<<" = "<<rate<<std::endl;
	}
}

void BitcoinExchange::checkMonth(double date[3], int &flag) const {
	if (date[1] < 1 || date[1] > 12) {
		std::cerr<<"Error: bad input => ";
		std::cerr<<date[0]<<"-"<<date[1]<<"-"<<date[2]<<std::endl;
		flag = 1;
	}
}

void BitcoinExchange::checkDay(double date[3], int &flag) const {
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (((int)date[0] % 4 == 0 && (int)date[0] % 100 != 0) || ((int)date[0] % 400 == 0))
		monthDays[1] = 29;
	if (date[2] < 1 || date[2] > monthDays[(int)date[1] - 1]) {
		std::cerr<<"Error: bad input => ";
		std::cerr<<date[0]<<"-"<<date[1]<<"-"<<date[2]<<std::endl;
		flag = 1;
	}
}

void BitcoinExchange::checkYear(double date[3], int &flag) const {
	if (date[0] < 1900 || date[0] > 2024) {
		std::cerr<<"Error: bad input => ";
		std::cerr<<date[0]<<"-"<<date[1]<<"-"<<date[2]<<std::endl;
		flag = 1;
	}
}

void BitcoinExchange::converDateToDouble(double date[3], std::string &str) const {
	std::string slice;

	slice = str.substr(0, str.find('-'));
	date[0] = std::strtod(&slice[0], NULL);
	slice = str.substr(str.find('-') + 1, str.find('-') - 2);
	date[1] = std::strtod(&slice[0], NULL);
	slice = str.substr(str.find('-') + 4, str.size());
	date[2] = std::strtod(&slice[0], NULL);
}

void BitcoinExchange::loadCSV(void) {
	std::fstream file;
	file.open("data.csv", std::fstream::in);

	if (file.is_open())
		this->loadCSVToData(file);	
	else 
		throw std::runtime_error("Could not open data.csv for reading!");
}
