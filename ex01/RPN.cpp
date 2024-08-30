#include "RPN.hpp"

void RPN::parse(char *arg) {
	this->args.assign(arg);

	IllegalSymbolCheck();
	loadStack();
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
	Data temp;

	while (str_trim >> tmp) {
		it = tmp.begin();
		if (isdigit(*it)) {
			temp.size = 4;
			temp.value = getNumber(tmp);
			this->stack_a.push(temp);
		}
		else {
			temp.size = 1;
			temp.value = getOperand(tmp);
			this->stack_a.push(temp);
		}
	}

	while (!this->stack_a.empty()) {
		std::cout<<this->stack_a.top().size<<std::endl;
		std::cout<<this->stack_a.top().value<<std::endl;
		this->stack_a.pop();
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
