
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
