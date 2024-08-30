
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>

class RPN {
	private:
		std::string args;
		std::stack<int> stack_a;
		int getNumber(std::string &str) const;
		char getOperand(std::string &str) const;
		void IllegalSymbolCheck(void);
		void loadStack(void);
	public:
		void parse(char *);
};

#endif
