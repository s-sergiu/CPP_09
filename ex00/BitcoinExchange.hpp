
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <stdexcept>
#include <set>
#include <fstream>
#include <ctime>

class BitcoinExchange {
		std::set<int> input;
	private:
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		void checkFileFormatting(std::fstream &) const;
		void checkFileHeader(std::fstream &) const;
		void checkFileValues(std::string &) const;
		void checkDateFormat(std::string &) const;
		void convertReadableTime(struct tm *) const;
		void checkDay(struct tm &) const;
		void checkYear(struct tm &) const;
		void checkMonth(struct tm &) const;
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		void parse(char *);
};

#endif
