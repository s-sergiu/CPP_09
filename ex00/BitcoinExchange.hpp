
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

class BitcoinExchange {
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange operator = (const BitcoinExchange &src);
		~BitcoinExchange(void);
		void parse(char **argv);
};

#endif
