
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>

class PmergeMe {
	private:
		int last;
		std::string args;
		std::vector<std::pair<int, int> > pairs;
		std::vector<int> list;
		std::vector<int> sublist;

		void illegalSymbolCheck(void);
		void createPairs(void);
		void extractPairFromOddList(void);
		void extractPairFromEvenList(void);
		void sortPairs(void);
		void insertLowerSort(void);
		std::vector<std::pair<int, int> >::iterator getMinValue(void);
		void printList(std::vector<int> &, std::string);
		void printPairedList(std::vector<std::pair<int, int> > &, std::string);
	public:
		PmergeMe(void);
		void parse(char**, int);
};

#endif
