
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>

class PmergeMe {
	private:
		std::string args;
		std::vector<int> vec;

		void IllegalSymbolCheck(void);
	public:
		void parse(char**, int);
};

#endif
