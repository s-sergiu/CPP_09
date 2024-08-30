
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>

struct Data {
	int size;
	int value;	
};

class RPN {
	private:
		std::string args;
		std::stack<Data> stack_a;
		std::stack<Data> stack_b;
		int getNumber(std::string &str) const;
		char getOperand(std::string &str) const;
		void IllegalSymbolCheck(void);
		void loadStack(void);
	public:
		void parse(char *);
};

#endif
