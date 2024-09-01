
#include "PmergeMe.hpp"

// Given an unsorted list, group the list into pairs. 
// If the list is odd, the last element is unpaired.

PmergeMe::PmergeMe(void) {
	last = -1;
}

void PmergeMe::printPairedList(std::vector<std::pair<int, int> > &list, std::string msg) {
	std::cout<<std::endl;
	std::cout<<"\e[44m-------------------------------\e[0m"<<std::endl;
	std::cout<<"\e[102m"<<msg<<"\e[0m"<<std::endl;
	std::cout<<"\e[44m--------------size-------------\e[0m"<<std::endl;
	std::cout<<"Paired list size: "<<list.size()<<std::endl;
	std::vector<std::pair <int, int> >::iterator it;

	std::cout<<"\e[44m-------------begin-------------\e[0m"<<std::endl;
	for(it = list.begin(); it != list.end(); ++it) {
		std::cout<<it->first<<" ";
		std::cout<<it->second<<" ";
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
	std::cout<<std::endl;
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
	sortPairs();
	printList(list, "after created and sort pairs");
	printPairedList(pairs, "after created and sort pairs");
	insertLowerSort();
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

void PmergeMe::sortPairs(void) {
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
		min = getMinValue();
		list.push_back(min->first);
		sublist.push_back(min->second);
		pairs.erase(min);
	}
}

