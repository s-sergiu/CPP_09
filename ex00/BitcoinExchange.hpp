
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <stdexcept>
#include <fstream>

class BitcoinExchange {
	private:
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		~BitcoinExchange(void);
		void checkFileFormatting(std::fstream &) const;
	public:
		BitcoinExchange(void);
		void parse(char *);
};

#endif
