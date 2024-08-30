
#include "PmergeMe.hpp"

void PmergeMe::parse(char *arg) {
	this->args.assign(arg);

	IllegalSymbolCheck();
}

void PmergeMe::IllegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it)
		if (!(isspace(*it) || isdigit(*it)))
			throw std::runtime_error("Illegal character");
}
