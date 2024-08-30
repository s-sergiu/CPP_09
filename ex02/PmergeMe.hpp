
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>

class PmergeMe {
	private:
		std::string args;
		std::vector<int*> pairs;
		std::vector<int> list;

		void illegalSymbolCheck(void);
		void createPairs(void);
	public:
		void parse(char**, int);
};

#endif
