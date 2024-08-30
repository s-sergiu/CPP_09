
#include "PmergeMe.hpp"

void PmergeMe::parse(char **arg, int argc) {
	for (int i = 1; i < argc; i++) {
		this->args.assign(arg[i]);
		IllegalSymbolCheck();
		std::cout<<arg[i]<<std::endl;
		vec.push_back(static_cast<int>(std::strtod(arg[i], NULL)));
	}


	std::cout<<"Before: ";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout<<vec[i]<<" ";
	std::cout<<std::endl;
}

void PmergeMe::IllegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it)
		if (!(isspace(*it) || isdigit(*it)))
			throw std::runtime_error("Illegal character");
}
