
#include "PmergeMe.hpp"

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
	int temp[2];
	while (!list.empty()) {
		temp[0] = *(list.end());
		list.pop_back();
		temp[1] = *(list.end());
		list.pop_back();
		pairs.push_back(temp);
	}

	std::cout<<"After: ";
	for (size_t i = 0; i < pairs.size(); i++) {
		std::cout<<"pair"<<std::endl;
		std::cout<<pairs[i][0]<<" ";
		std::cout<<pairs[i][1]<<" ";
	}
	std::cout<<std::endl;
}
