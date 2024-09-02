
#include "PmergeMe.hpp"

// Given an unsorted list, group the list into pairs. 
// If the list is odd, the last element is unpaired.

PmergeMe::PmergeMe(int argc) {
	last = -1;
	elements = argc - 1;
}

void PmergeMe::endSecondClock(void) {
	this->end = std::clock();
	this->elapsed_second = (double) (this->end - this->start) / CLOCKS_PER_SEC;
}

void PmergeMe::printTime(void) {
	std::cout<<std::fixed;

	std::cout<<"Time to process a range of "<<elements;
	std::cout<<" elements with std::[vector_pair] :";
	std::cout<<"elasped: "<<this->elapsed_first<<std::endl;
	std::cout<<"Time to process a range of "<<elements;
	std::cout<<" elements with std::[vector] :";
	std::cout<<"elasped: "<<this->elapsed_second<<std::endl;
}
void PmergeMe::endFirstClock(void) {
	this->end = std::clock();
	this->elapsed_first = (double) (this->end - this->start) / CLOCKS_PER_SEC;
}

void PmergeMe::startClock(void) {
	this->start = std::clock();
}

void PmergeMe::printList(vector &list, std::string msg) {
	vector::iterator it;
	std::cout<<msg<<":    ";
	int i = 0;
	for(it = list.begin(); it != list.end(); ++it) {
		std::cout<<*it<<" ";
		if (i++ == 10) {
			std::cout<<" [...] ";
			break ;
		}
	}
	std::cout<<std::endl;
}

void PmergeMe::parse(char **arg, int argc) {
	for (int i = 1; i < argc; i++) {
		this->args.assign(arg[i]);
		illegalSymbolCheck();
		list.push_back(static_cast<int>(std::strtod(arg[i], NULL)));
	}
	printList(list, "Before");
	startClock();
		createPairs();
		sortSinglePairs();
		mergeSortPair(pairs, 0, pairs.size() - 1);
	endFirstClock();
	startClock();
		separatePairs();
		insertionSort();
	endSecondClock();
	printList(list, "After");
	printTime();
}

void PmergeMe::illegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it)
		if (!(isspace(*it) || isdigit(*it)))
			throw std::runtime_error("Illegal character");
}

void PmergeMe::extractPairFromEvenList(void) {
	pair temp;

	while (!list.empty()) {
		if (*(list.begin()) < *(list.begin() + 1)) {
			temp.first = list.front();
			list.erase(list.begin());
			temp.second = list.front();
			list.erase(list.begin());
		} else {
			temp.second = list.front();
			list.erase(list.begin());
			temp.first = list.front();
			list.erase(list.begin());
		}
		pairs.push_back(temp);
	}
}

void PmergeMe::extractPairFromOddList(void) {
	pair temp;

	last = list.back();
	list.pop_back();
	while (!list.empty()) {
		if (*(list.begin()) < *(list.begin() + 1)) {
			temp.first = list.front();
			list.erase(list.begin());
			temp.second = list.front();
			list.erase(list.begin());
		} else {
			temp.second = list.front();
			list.erase(list.begin());
			temp.first = list.front();
			list.erase(list.begin());
		}
		pairs.push_back(temp);
	}
}

void PmergeMe::createPairs(void) {
	if (list.size() % 2 == 0)
		extractPairFromEvenList();
	else
		extractPairFromOddList();
}

void PmergeMe::sortSinglePairs(void) {
	vector_pair::iterator it;
	int temp;

	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first > it->second) {
			temp = it->second;	
			it->second = it->first;
			it->first = temp;
		}
	}
}

vector_pair::iterator PmergeMe::getMaxValue(void) {
	vector_pair::iterator max;
	vector_pair::iterator it;

	max = pairs.begin();
	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first < max->first)
			max = it;
	}

	return max;
}

vector_pair::iterator PmergeMe::getMinValue(void) {
	vector_pair::iterator min;
	vector_pair::iterator it;

	min = pairs.begin();
	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first > min->first)
			min = it;
	}

	return min;
}

void PmergeMe::separatePairs(void) {
	vector_pair::iterator it;
	vector_pair::iterator min;

	while (!pairs.empty()) {
		min = getMaxValue();
		list.push_back(min->first);
		sublist.push_back(min->second);
		pairs.erase(min);
	}
	if (last != -1)
		sublist.push_back(last);
}

vector_pair PmergeMe::fillVector(vector_pair &arg, int size, int start) {
    vector_pair vec(size);

	for (unsigned int i = 0; i < vec.size(); ++i)
		vec[i] = arg[start + i];
	return vec;
}

void PmergeMe::merge(vector_pair &arr, int start, int middle, int end) {

    vector_pair left;
    vector_pair right;
    unsigned int l = 0;
	unsigned int r = 0;
    unsigned int i = start;

	left = fillVector(arr, middle - start + 1, start);
	right = fillVector(arr, end - middle, middle + 1);

    while (l < left.size() && r < right.size()) {
        if (left[l] <= right[r])
            arr[i] = left[l++];
		else
            arr[i] = right[r++];
        i++;
    }
    while (l < left.size())
		arr[i++] = left[l++];
    while (r < right.size())
		arr[i++] = right[r++];
}

void PmergeMe::mergeSortPair(vector_pair &vec, int start, int end)
{
	if (start < end) {
		int middle = (start + end) / 2;
		mergeSortPair(vec, start, middle);
		mergeSortPair(vec, middle + 1, end);
		merge(vec, start, middle, end);
	}
}

void PmergeMe::insertionSort(void)
{
	unsigned int j = 0;
	unsigned int i = list.size() - 1;
	vector::iterator it;
	int a;

	while (!sublist.empty()) {
		it = sublist.begin();

		a = *it;
		i = j + 1;
		while (i < list.size() && list[i] < a)
			i++;
		j++;
		list.insert(list.begin() + i,a);
		sublist.erase(sublist.begin());
	}
}
