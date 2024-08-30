#include "RPN.hpp"

// Constructor

RPN::RPN(void) {

}

RPN::RPN(const RPN &src) {
	(void)src;
}

RPN RPN::operator = (const RPN &src) {
	(void)src;
	return *this;
}

RPN::~RPN(void) {

}

// Class functions

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
	std::stringstream ss(this->args);
	std::string tmp;

	while (ss >> tmp)
		if (isdigit(*(tmp.begin())))
			this->stack_a.push(getNumber(tmp));
		else if (this->stack_a.size() == 1)
			throw std::runtime_error("Incorrect stack structure");
		else
			handleOperator(getOperand(tmp));
	if (stack_a.size() > 1)
		throw std::runtime_error("Stack is not empty...");
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
