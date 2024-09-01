
#include "PmergeMe.hpp"

// Given an unsorted list, group the list into pairs. 
// If the list is odd, the last element is unpaired.

PmergeMe::PmergeMe(void) {
	last = -1;
}

void PmergeMe::printPairedList(std::vector<std::pair<int, int> > &list) {
	std::cout<<"--------------size-------------"<<std::endl;
	std::cout<<"List size: "<<list.size()<<std::endl;
	std::vector<std::pair <int, int> >::iterator it;

	std::cout<<"-------------begin-------------"<<std::endl;
	for(it = list.begin(); it != list.end(); ++it) {
		std::cout<<it->first<<" ";
		std::cout<<it->second<<" ";
		std::cout<<"| ";
	}
	std::cout<<std::endl;
	std::cout<<"--------------end--------------"<<std::endl;
}

void PmergeMe::printList(std::vector<int> &list) {
	std::cout<<"--------------size-------------"<<std::endl;
	std::cout<<"List size: "<<list.size()<<std::endl;
	std::vector<int>::iterator it;

	std::cout<<"-------------begin-------------"<<std::endl;
	for(it = list.begin(); it != list.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
	std::cout<<"--------------end--------------"<<std::endl;
}

void PmergeMe::parse(char **arg, int argc) {
	for (int i = 1; i < argc; i++) {
		this->args.assign(arg[i]);
		illegalSymbolCheck();
		list.push_back(static_cast<int>(std::strtod(arg[i], NULL)));
	}
	printList(list);
	createPairs();
	printPairedList(pairs);
	sortPairs();
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
		temp.first = list.front();
		list.erase(list.begin());
		temp.second = list.front();
		list.erase(list.begin());
		pairs.push_back(temp);
	}
}

void PmergeMe::extractPairFromOddList(void) {
	std::pair<int, int> temp;

	while (!list.empty()) {
		if (list.size() == 1) {
			last = list[0];
			list.pop_back();
			break ;
		}
		temp.first = list.back();
		list.pop_back();
		temp.second = list.back();
		list.pop_back();
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

