
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <stdexcept>
#include <set>
#include <fstream>

class BitcoinExchange {
		std::set<int> input;
	private:
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		void checkFileFormatting(std::fstream &) const;
		void checkFileHeader(std::fstream &) const;
		void checkFileValues(std::string &) const;
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		void parse(char *);
};

#endif
