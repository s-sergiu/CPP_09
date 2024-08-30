#include "RPN.hpp"

void RPN::parse(char *arg) {
	this->args.assign(arg);

	IllegalSymbolCheck();
	loadStack();
	std::cout<<this->stack_a.top()<<std::endl;
}

void RPN::IllegalSymbolCheck(void) {
	for(std::string::iterator it = args.begin(); it != args.end(); ++it) {
		if (!(isspace(*it) || isdigit(*it) || 
			*it == '+' || *it == '-' || *it == '/' || *it == '*'))
			throw std::runtime_error("Illegal character");
	}
}

void RPN::loadStack(void) {
	std::stringstream str_trim(this->args);
	std::string tmp;
	std::string::iterator it;
	int temp_nb;

	// 7 3 * 10 -
	while (str_trim >> tmp) {
		it = tmp.begin();
		if (isdigit(*it))
			this->stack_a.push(getNumber(tmp));
		else {
			if (getOperand(tmp) == '*') {
				temp_nb = this->stack_a.top();
				this->stack_a.pop();
				this->stack_a.top() *= temp_nb;
			}
			else if (getOperand(tmp) == '-') {
				temp_nb = this->stack_a.top();
				this->stack_a.pop();
				this->stack_a.top() -= temp_nb;
			}
			else if (getOperand(tmp) == '/') {
				temp_nb = this->stack_a.top();
				this->stack_a.pop();
				this->stack_a.top() /= temp_nb;
			}
			else if (getOperand(tmp) == '+') {
				temp_nb = this->stack_a.top();
				this->stack_a.pop();
				this->stack_a.top() += temp_nb;
			}
		}
	}
}

char RPN::getOperand(std::string &str) const {
	char operand;

	operand = static_cast<char>(str[0]);
	return operand;
}

int RPN::getNumber(std::string &str) const {
	int number;

	number = static_cast<int>(std::strtod(&str[0], NULL));
	return number;
}
