#include "List.h"
#include <cassert>
#include <string>
#include <cstddef>

// SHORT DESCRIPTION OF TEST CASE
// Testing overloaded operators
// If you have multiple test cases in this file, put prototypes
// for test functions here
using namespace std;

void test_iterator_constructor_and_operators();
void test_iterator_equals_not_equals();

int main()
{
	test_iterator_constructor_and_operators();
	test_iterator_equals_not_equals();

	cout << "All Tests for List::Iterator Passed" << endl;
    return 0;
}

void test_iterator_constructor_and_operators() {

	List<int> list1;

	for (int i = 0; i <= 100; i += 10) {
		list1.push_back(i);
	}

	List<int>::Iterator iter_front = list1.begin();
	List<int>::Iterator iter_back = list1.begin();

	for (int i = 0; i < list1.size() - 1; ++i) {
		++iter_back;
	}

	assert(*iter_front == 0);
	assert(*iter_back == 100);

	int i = 0;

	List<int>::Iterator iter_temp;
	assert(iter_temp == list1.end());

	for (List<int>::Iterator j = iter_front; j != list1.end(); ++j) {
		
		assert(*j == i);

		if (*j == 30) {
			iter_temp = j;
		}

		i += 10;
	}

	i -= 10;

	for (List<int>::Iterator j = iter_back; j != list1.begin(); --j) {

		assert(*j == i);
		i -= 10;
	}

	assert(*------iter_temp == 0);
	assert(*++++++iter_temp == 30);
	assert(*--++++--++iter_temp == 40);

	cout << "Tests for Iterator Constructor Passed" << endl;
	cout << "Tests for Iterator Decrement Passed" << endl;
	cout << "Tests for Iterator Increment Passed" << endl;
	cout << "Tests for Iterator Dereference Passed" << endl;

	return;
}

void test_iterator_equals_not_equals() {

	List<int> list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(0);

	List<int>::Iterator iter_front = list1.begin();
	List<int>::Iterator iter_back = list1.begin();

	List<int>::Iterator iter_temp;

	assert(iter_front == iter_back);
	assert(iter_front != iter_temp && iter_back != iter_temp);

	for (int i = 0; i < list1.size() - 1; ++i) {
		++iter_back;
	}

	assert(iter_front == iter_front && iter_back == iter_back && iter_temp == iter_temp);
	assert(iter_front != iter_back);
	iter_temp = iter_back;
	--iter_temp;
	assert(iter_front != iter_temp && iter_back != iter_temp);
	----iter_temp;
	assert(iter_front == iter_temp && iter_temp != iter_back && iter_front != iter_back);

	cout << "Tests for Iterator Equal Passed" << endl;
	cout << "Tests for Iterator Not Equal Passed" << endl;

	return;
}