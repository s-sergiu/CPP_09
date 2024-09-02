
#include "PmergeMe.hpp"

int main (int argc, char **argv) {
	PmergeMe obj(argc);

	if (argc > 2) {
		try {
			obj.parse(argv, argc);
		} catch (std::exception &e) {
			std::cerr<<"Exception: "<<e.what()<<std::endl;
		}
	}
	else
		std::cerr<<"Usage: ./PmergeMe 3 5 9 7 4"<<std::endl;
	return 0;
}
