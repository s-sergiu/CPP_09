
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {
	last = NULL;
}

void PmergeMe::parse(char **arg, int argc) {
	for (int i = 1; i < argc; i++) {
		this->args.assign(arg[i]);
		illegalSymbolCheck();
		std::cout<<arg[i]<<std::endl;
		list.push_back(static_cast<int>(std::strtod(arg[i], NULL)));
	}


	std::cout<<"Before: ";
	for (size_t i = 0; i < list.size(); i++)
		std::cout<<list[i]<<" ";
	std::cout<<std::endl;
	createPairs();
	sortPairs();
	insertLowerSort();

	for(std::vector<int>::iterator it = list.begin(); it != list.end(); ++it)
		std::cout<<"list fin: "<<*it<<std::endl;
	for(std::vector<int>::iterator it = sublist.begin(); it != sublist.end(); ++it)
		std::cout<<"sublist: "<<*it<<std::endl;
}

void PmergeMe::illegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it)
		if (!(isspace(*it) || isdigit(*it)))
			throw std::runtime_error("Illegal character");
}

void PmergeMe::createPairs(void) {
	std::pair<int, int> temp;
	std::cout<<"last: "<<list.back()<<std::endl;

	while (!list.empty()) {
		if (list.size() == 1) {
			last = &list.back();
			list.pop_back();
			std::cout<<list[0]<<std::endl;
			break ;
		}
		temp.first = list.back();
		list.pop_back();
		temp.second = list.back();
		list.pop_back();
		pairs.push_back(temp);
	}

	std::cout<<"After: "<<std::endl;
	for (size_t i = 0; i < pairs.size(); i++) {
		std::cout<<"pair: ";
		std::cout<<pairs[i].first<<" ";
		std::cout<<pairs[i].second<<" ";
		std::cout<<std::endl;
	}
	if (last) {
		std::cout<<"last: "<<*last;
		std::cout<<std::endl;
	}
}

void PmergeMe::sortPairs(void) {
	std::vector<std::pair<int, int> >::iterator it;
	int temp;
	std::cout<<"beginnnn: "<<std::endl;
	for(it = pairs.begin(); it != pairs.end(); ++it) {
		// sort pairs
		if (it->first > it->second) {
			temp = it->second;	
			it->second = it->first;
			it->first = temp;
		}
		std::cout<<"lowest: "<<it->first<<std::endl;
		std::cout<<"highest: "<<it->second<<std::endl;
	}
	//pairs sorted
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

	sublist.push_back(*last);
	std::cout<<"min : "<<std::endl;
	min = getMinValue();
	std::cout<<min->first<<std::endl;
	list.push_back(min->first);
	sublist.push_back(min->second);
	pairs.erase(min);
	std::cout<<"min : "<<std::endl;
	min = getMinValue();
	std::cout<<min->first<<std::endl;
	list.push_back(min->first);
	sublist.push_back(min->second);
	pairs.erase(min);
	std::cout<<"min : "<<std::endl;
	min = getMinValue();
	std::cout<<min->first<<std::endl;
	list.push_back(min->first);
	sublist.push_back(min->second);
	pairs.erase(min);
	std::cout<<"min : "<<std::endl;
	min = getMinValue();
	std::cout<<min->first<<std::endl;
	list.push_back(min->first);
	sublist.push_back(min->second);
	pairs.erase(min);
	//pairs sorted
}

