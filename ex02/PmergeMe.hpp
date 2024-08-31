
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include <algorithm>

class PmergeMe {
	private:
		int *last;
		std::string args;
		std::vector<std::pair<int, int> > pairs;
		std::vector<int> list;
		std::vector<int> sublist;

		void illegalSymbolCheck(void);
		void createPairs(void);
		void sortPairs(void);
		void insertLowerSort(void);
	public:
		PmergeMe(void);
		void parse(char**, int);
};

#endif
