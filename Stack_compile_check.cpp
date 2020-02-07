#include "Stack.h"
#include <iostream>

using std::cout;
using std::endl;

bool is_even(int a) {

	if (a % 2 == 0) {
		return true;
	} else {
		return false;
	}
}

bool is_odd(int a) {
	if (a % 2 != 0) {
		return true;
	} else {
		return false;
	}
}

int main() {

	Stack<int> stack;

	assert(stack.empty());
	assert(stack.size() == 0);

	stack.push(10);
	assert(stack.top() == 10);
	stack.push(11);
	assert(stack.top() == 11);

	stack.print(cout);
	cout << endl;

	assert(stack.count_if(is_even) == 1);
	cout << stack.count_if(is_even) << endl;
	assert(stack.count_if(is_odd) == 1);
	cout << stack.count_if(is_odd) << endl;

	assert(!stack.empty());
	assert(stack.size() == 2);

	stack.pop();
	assert(stack.top() == 10);

	assert(!stack.empty());
	assert(stack.size() == 1);

	cout << "Compilation tests passed" << endl;

	return 0;
}