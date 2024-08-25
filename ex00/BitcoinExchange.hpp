
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

class BitcoinExchange {
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator = (const BitcoinExchange &);
		~BitcoinExchange(void);
		void parse(char **);
};

#endif
