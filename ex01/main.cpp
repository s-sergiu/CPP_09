#include "RPN.hpp"

int main(int argc, char **argv) {
	RPN obj;

	if (argc == 2) {
		try {
			obj.parse(argv[1]);
		} catch (std::exception &e) {
			std::cerr<<"Exception: "<<e.what()<<std::endl;
		}
	}
	else
		std::cerr<<"Usage: ./RPN \"8 9 * 9 - 9 - 4 - 1 +\""<<std::endl;
	return 0;
}
