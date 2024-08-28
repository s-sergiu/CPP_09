
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <stdexcept>
#include <map>
#include <fstream>
#include <cstdlib>

class BitcoinExchange {
	private:
		std::map<std::string, double> data;
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		void checkFileFormatting(std::fstream &);
		void loadCSVToData(std::fstream &);
		void checkFileHeader(std::fstream &) const;
		void checkCSVHeader(std::fstream &file) const;
		void checkDateValues(std::string &, int &) const;
		void checkNumericValues(std::string &);
		void checkDateFormat(std::string &) const;
		void converDateToDouble(double [3], std::string &) const;
		void checkDay(double [3], int &) const;
		void checkYear(double [3], int &) const;
		void checkMonth(double [3], int &) const;
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		void parse(char *);
		void loadCSV(void);
};

#endif
