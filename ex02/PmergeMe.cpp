
#include "PmergeMe.hpp"

// Given an unsorted list, group the list into pairs. 
// If the list is odd, the last element is unpaired.

PmergeMe::PmergeMe(void) {
	last = -1;
}

void PmergeMe::printPairedList(vector_pair &list, std::string msg, int level) {
	std::cout<<"\e[44m-------------------------------\e[0m"<<std::endl;
	std::cout<<"\e[102m"<<msg<<"\e[0m"<<std::endl;
	std::cout<<"\e[44m--------------size-------------\e[0m"<<std::endl;
	std::cout<<"Paired list size: "<<list.size()<<std::endl;
	vector_pair::iterator it;

	std::cout<<"\e[44m-------------begin-------------\e[0m"<<std::endl;
	for(it = list.begin(); it != list.end(); ++it) {
		if (level == 0 || level == 1)
			std::cout<<it->first<<" ";
		if (level == 0 || level == 2)
			std::cout<<it->second<<" ";
		if (level == 0)
			std::cout<<"| ";
	}
	if (list.empty())
		std::cout<<"\e[31mList is empty!\e[0m";
	std::cout<<std::endl;
	if (last != -1)
		std::cout<<"\e[32mLast is: "<<this->last<<"\e[0m"<<std::endl;
	std::cout<<"\e[44m--------------end--------------\e[0m"<<std::endl;
	std::cout<<std::endl;
}

void PmergeMe::printList(vector &list, std::string msg) {
	std::cout<<"\e[45m-------------------------------\e[0m"<<std::endl;
	std::cout<<"\e[102m"<<msg<<"\e[0m"<<std::endl;
	std::cout<<"\e[45m--------------size-------------\e[0m"<<std::endl;
	std::cout<<"List size: "<<list.size()<<std::endl;
	vector::iterator it;

	std::cout<<"\e[45m-------------begin-------------\e[0m"<<std::endl;
	for(it = list.begin(); it != list.end(); ++it)
		std::cout<<*it<<" ";
	if (list.empty())
		std::cout<<"\e[31mList is empty!\e[0m";
	std::cout<<std::endl;
	if (last != -1) {
		std::cout<<"\e[32mLast is: "<<this->last<<"\e[0m"<<std::endl;
	}
	std::cout<<"\e[45m--------------end--------------\e[0m"<<std::endl;
	std::cout<<std::endl;
}

void PmergeMe::parse(char **arg, int argc) {
	for (int i = 1; i < argc; i++) {
		this->args.assign(arg[i]);
		illegalSymbolCheck();
		list.push_back(static_cast<int>(std::strtod(arg[i], NULL)));
	}
	printList(list, "initial");
	createPairs();
	sortSinglePairs();
	printList(list, "after created and sort pairs");
	printPairedList(pairs, "after created and sort pairs", 0);
	mergeSortPair(pairs, 0, pairs.size() - 1);
	printPairedList(pairs, "after merge sort" , 0);
	insertLowerSort();
	printList(list, "list");
	printList(sublist, "sublist");
	insertionSort();
	printList(list, "list");
	printList(sublist, "sublist");
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

void PmergeMe::insertLowerSort(void) {
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
		while (i > 0 && list[i] < a)
			i++;
		j++;
		list.insert(list.begin() + i,a);
		sublist.erase(sublist.begin());
	}
}
