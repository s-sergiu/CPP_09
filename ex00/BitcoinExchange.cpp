
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	(void)src;
}

BitcoinExchange BitcoinExchange::operator = (const BitcoinExchange &src) {
	(void)src;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {

}

void BitcoinExchange::parse(char **argv) {
	(void)argv;
}
