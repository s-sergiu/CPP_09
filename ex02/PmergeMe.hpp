
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
		void sortSinglePairs(void);
		void mergeSort(void);
		void merge(std::vector<std::pair<int, int> > &, int, int, int);
		void mergeSortPair(std::vector<std::pair<int ,int> > &, int, int);
		void insertLowerSort(void);
		std::vector<std::pair<int, int> >::iterator getMinValue(void);
		std::vector<std::pair<int, int> >::iterator getMaxValue(void);
		void printList(std::vector<int> &, std::string);
		void printPairedList(std::vector<std::pair<int, int> > &, std::string, int);
	public:
		PmergeMe(void);
		void parse(char**, int);
};

#endif
