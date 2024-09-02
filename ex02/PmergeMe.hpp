
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <iomanip>
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
		int elements;
		std::clock_t start;
		std::clock_t end;
		double elapsed_first;
		double elapsed_second;
		std::string args;
		vector_pair pairs;
		vector list;
		vector sublist;

		void illegalSymbolCheck(void);
		void startClock(void);
		void endFirstClock(void);
		void endSecondClock(void);
		void createPairs(void);
		void extractPairFromOddList(void);
		void extractPairFromEvenList(void);
		void sortSinglePairs(void);
		void merge(vector_pair &, int, int, int);
		void mergeSortPair(vector_pair &, int, int);
		void separatePairs(void);
		vector_pair::iterator getMinValue(void);
		vector_pair::iterator getMaxValue(void);
		void printList(vector &, std::string);
		void printTime(void);
		vector_pair fillVector(vector_pair &, int, int);
		void insertionSort();
	public:
		PmergeMe(int);
		void parse(char**, int);
};

#endif
