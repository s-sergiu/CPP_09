
#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int main(int argc, char **argv) {
	(void)argv;
	BitcoinExchange obj;
	if (argc == 2)	
		try {
			obj.parse(argv);	
		} catch(std::exception &e) {
			std::cerr<<"Error: "<<e.what()<<std::endl;
		}
	else {
		std::cerr<<"Invalid number of arguments!"<<std::endl;
	}
	return 0;
}
