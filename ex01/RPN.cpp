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

void RPN::handleOperator(char operand) {
	this->buffer = this->stack_a.top();
	this->stack_a.pop();

	if (operand == '*')
		this->stack_a.top() *= this->buffer;
	else if (operand == '-')
		this->stack_a.top() -= this->buffer;
	else if (operand == '/')
		this->stack_a.top() /= this->buffer;
	else
		this->stack_a.top() += this->buffer;
}

void RPN::loadStack(void) {
	std::stringstream str_trim(this->args);
	std::string tmp;
	std::string::iterator it;

	// 7 3 * 10 -
	while (str_trim >> tmp) {
		it = tmp.begin();
		if (isdigit(*it))
			this->stack_a.push(getNumber(tmp));
		else
			handleOperator(getOperand(tmp));
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
