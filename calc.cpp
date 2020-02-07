#include "Stack.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

// HUGE NOTE: CHECK REQUIRED CONDITION FOR EACH FUNCTION, WRITE FUNCTION ACCORDINGLY TO THE FUNCTION

class Same_num {

	double match_num;

public:

	Same_num(double input) : match_num(input) {}

	bool operator() (double d) {
		return match_num == d;
	}
};

void multiple(Stack<double> &stack) {
	assert(stack.size() >= 2);
	double multiple = stack.pop() * stack.pop();
	stack.push(multiple);
}

void subtract(Stack<double> &stack) {
	assert(stack.size() >= 2);
	double first = stack.pop();
	double second = stack.pop();
	double subtract = second - first;
	stack.push(subtract);
}

void addition(Stack<double> &stack) {
	assert(stack.size() >= 2);
	double first = stack.pop();
	double second = stack.pop();
	double addition = first + second;
	stack.push(addition);
}

void divide(Stack<double> &stack) {
	assert(stack.size() >= 2);
	double denom = stack.pop();
	double frac = stack.pop();
	if (denom == 0) {
		cout << "Error: Division by zero" << endl;
		stack.push(frac);
		stack.push(denom);
	}
	else {
	double devide = frac / denom;
	stack.push(devide);
	}
}

void duplicate(Stack<double> &stack) {
	assert(stack.size() >= 1);
	double dup = stack.pop();
	stack.push(dup);
	stack.push(dup);
}

void reverse(Stack<double> &stack) {
	assert(stack.size() >= 2);
	double first = stack.pop();
	double second = stack.pop();
	stack.push(first);
	stack.push(second);
}

void clear(Stack<double> &stack) {
	while(!stack.empty()) {
		stack.pop();
	}
}

void print(Stack<double> &stack) {
	assert(!stack.empty());
	cout << stack.top() << endl;
}

void print_all(Stack<double> &stack) {
	stack.print(cout);
	cout << endl;
}

void negate_num(Stack<double> &stack) {
	double negate = -1 * stack.pop();
	stack.push(negate);
}

void match(Stack<double> &stack) {

	double match = stack.pop();
	double match_num = stack.count_if(Same_num(match));
	stack.push(match_num);
}

int main() {

	cout.precision(4);
	string input;
	Stack<double> stack;
	while(cin >> input) {
		if (input == "+") {
			addition(stack);
		}
		else if (input == "-") {
			subtract(stack);
		}
		else if (input == "*") {
			multiple(stack);
		}
		else if (input == "/") {
			divide(stack);
		}
		else if (input == "d") {
			duplicate(stack);
		}
		else if (input == "r") {
			reverse(stack);
		}
		else if (input == "c") {
			clear(stack);
		}
		else if (input == "a") {
			print_all(stack);
		}
		else if (input == "q") {
			return 0;
		}
		else if (input == "p") {
			print(stack);
		}
		else if (input == "n") {
			negate_num(stack);
		}
		else if (input == "m") {
			match(stack);
		}
		else {
			const char * num = input.c_str();
			double number = atof(num);
			stack.push(number);
		}
	}
	
	return 0;
}