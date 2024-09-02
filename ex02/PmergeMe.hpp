
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <exception>

typedef std::pair<int, int> pair;
typedef std::vector<int> vector;
typedef std::vector<pair> vector_pair;

class PmergeMe {
	private:
		int last;
		std::string args;
		vector_pair pairs;
		vector list;
		vector sublist;

		void illegalSymbolCheck(void);
		void createPairs(void);
		void extractPairFromOddList(void);
		void extractPairFromEvenList(void);
		void sortSinglePairs(void);
		void merge(vector_pair &, int, int, int);
		void mergeSortPair(vector_pair &, int, int);
		void insertLowerSort(void);
		vector_pair::iterator getMinValue(void);
		vector_pair::iterator getMaxValue(void);
		void printList(vector &, std::string);
		vector_pair fillVector(vector_pair &, int, int);
		void insertionSort();
	public:
		PmergeMe(void);
		void parse(char**, int);
};

#endif
