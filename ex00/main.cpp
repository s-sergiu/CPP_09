
#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
	(void)argv;
	BitcoinExchange obj;
	if (argc == 2)	
		try {
			obj.loadCSV();
			obj.parse(argv[1]);	
		} catch(std::exception &e) {
			std::cerr<<"Error: "<<e.what()<<std::endl;
		}
	else 
		std::cerr<<"Usage: ./btc file"<<std::endl;
	return 0;
}
