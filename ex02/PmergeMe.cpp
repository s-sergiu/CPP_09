
#include "PmergeMe.hpp"

// Given an unsorted list, group the list into pairs. 
// If the list is odd, the last element is unpaired.

PmergeMe::PmergeMe(void) {
	last = -1;
}

void PmergeMe::printPairedList(std::vector<std::pair<int, int> > &list, std::string msg, int level) {
	std::cout<<"\e[44m-------------------------------\e[0m"<<std::endl;
	std::cout<<"\e[102m"<<msg<<"\e[0m"<<std::endl;
	std::cout<<"\e[44m--------------size-------------\e[0m"<<std::endl;
	std::cout<<"Paired list size: "<<list.size()<<std::endl;
	std::vector<std::pair <int, int> >::iterator it;

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

void PmergeMe::printList(std::vector<int> &list, std::string msg) {
	std::cout<<"\e[45m-------------------------------\e[0m"<<std::endl;
	std::cout<<"\e[102m"<<msg<<"\e[0m"<<std::endl;
	std::cout<<"\e[45m--------------size-------------\e[0m"<<std::endl;
	std::cout<<"List size: "<<list.size()<<std::endl;
	std::vector<int>::iterator it;

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
	//insertLowerSort();
}

void PmergeMe::illegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it)
		if (!(isspace(*it) || isdigit(*it)))
			throw std::runtime_error("Illegal character");
}

void PmergeMe::extractPairFromEvenList(void) {
	std::pair<int, int> temp;

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
	std::pair<int, int> temp;

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
	std::vector<std::pair<int, int> >::iterator it;
	int temp;

	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first > it->second) {
			temp = it->second;	
			it->second = it->first;
			it->first = temp;
		}
	}
}

std::vector<std::pair<int, int> >::iterator PmergeMe::getMaxValue(void) {
	std::vector<std::pair<int, int> >::iterator max;
	std::vector<std::pair<int, int> >::iterator it;

	max = pairs.begin();
	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first < max->first)
			max = it;
	}

	return max;
}

std::vector<std::pair<int, int> >::iterator PmergeMe::getMinValue(void) {
	std::vector<std::pair<int, int> >::iterator min;
	std::vector<std::pair<int, int> >::iterator it;

	min = pairs.begin();
	for(it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first > min->first)
			min = it;
	}

	return min;
}

void PmergeMe::insertLowerSort(void) {
	std::vector<std::pair<int, int> >::iterator it;
	std::vector<std::pair<int, int> >::iterator min;

	while (!pairs.empty()) {
		min = getMaxValue();
		list.push_back(min->first);
		sublist.push_back(min->second);
		pairs.erase(min);
	}
	if (last != -1)
		sublist.push_back(last);
}

void PmergeMe::mergeSort() {
	int len;
	std::vector<std::pair<int, int> > temp;
	std::vector<std::pair<int, int> >::iterator it;

	len = pairs.size() / 2;
	if (pairs.size() > 1)
		std::cout<<"we can mergesort"<<std::endl;

	std::cout<<"half len is: "<<len<<std::endl;
	if (pairs.begin() > pairs.end()) {
		temp.push_back(pairs.back());
		temp.push_back(pairs.front());
	}
	else {
		temp.push_back(pairs.front());
		temp.push_back(pairs.back());
	}
	printPairedList(temp, "temp", 0);
}

void PmergeMe::merge(std::vector<std::pair<int, int> > &arr, int start, int middle, int end) {

    std::vector<std::pair<int, int> > leftArray(middle - start + 1);
    std::vector<std::pair<int, int> > rightArray(end - middle);
    unsigned int l = 0;
	unsigned int r = 0;
    unsigned int i = start;

    for (unsigned int i = 0; i < leftArray.size(); ++i)
        leftArray[i] = arr[start + i];
    for (unsigned int i = 0; i < rightArray.size(); ++i)
        rightArray[i] = arr[middle + 1 + i];

    while (l < leftArray.size() && r < rightArray.size()) {
        if (leftArray[l] <= rightArray[r]) {
            arr[i] = leftArray[l];
            l++;
        } else {
            arr[i] = rightArray[i];
            r++;
        }
        i++;
    }
    while (l < leftArray.size())
		arr[i++] = leftArray[l++];
    while (r < rightArray.size())
		arr[i++] = rightArray[r++];
}

void PmergeMe::mergeSortPair(std::vector<std::pair<int ,int> > &vec, int start, int end)
{
	if (start < end) {
		int middle = (start + end) / 2;
		mergeSortPair(vec, start, middle);
		mergeSortPair(vec, middle + 1, end);
		merge(vec, start, middle, end);
	}
}
