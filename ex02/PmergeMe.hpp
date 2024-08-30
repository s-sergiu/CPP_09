
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <exception>

class PmergeMe {
	private:
		std::string args;

		void IllegalSymbolCheck(void);
	public:
		void parse(char *arg);
};

#endif
