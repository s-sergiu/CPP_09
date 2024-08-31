
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>

class PmergeMe {
	private:
		int *last;
		std::string args;
		std::vector<std::pair<int, int> > pairs;
		std::vector<int> list;

		void illegalSymbolCheck(void);
		void createPairs(void);
	public:
		PmergeMe(void);
		void parse(char**, int);
};

#endif
