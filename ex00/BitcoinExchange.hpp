
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <stdexcept>
#include <set>
#include <fstream>
#include <cstdlib>

class BitcoinExchange {
		std::set<int> input;
	private:
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		void checkFileFormatting(std::fstream &) const;
		void checkFileHeader(std::fstream &) const;
		void checkDateValues(std::string &) const;
		void checkNumericValues(std::string &) const;
		void checkDateFormat(std::string &) const;
		void converDateToDouble(double [3], std::string &) const;
		void checkDay(double [3], int &) const;
		void checkYear(double [3], int &) const;
		void checkMonth(double [3], int &) const;
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		void parse(char *);
};

#endif
