
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>

#define ADD +
#define MIN -
#define DIV /
#define MUL *

class RPN {
	private:
		int buffer;
		std::string args;
		std::stack<int> stack_a;

		int getNumber(std::string &str) const;
		char getOperand(std::string &str) const;
		void IllegalSymbolCheck(void);
		void loadStack(void);
		void handleOperator(char);
	public:
		void parse(char *);
};

#endif
