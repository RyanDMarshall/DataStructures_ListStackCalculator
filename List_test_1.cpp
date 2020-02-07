#include "List.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

// SHORT DESCRIPTION OF TEST CASE

// If you have multiple test cases in this file, put prototypes
// for test functions here

void test_empty();
void test_size();
void test_front();
void test_back();
void test_push_front();
void test_push_back();
void test_pop_front();
void test_pop_back();
void test_big_three();
void test_erase_small();
void test_erase();
void test_multiple_erase();
void test_insert();
void test_multiple_insert();

int main()
{
	test_empty();
	test_size();
	test_front();
	test_back();
	test_push_front();
	test_push_back();
	test_pop_front();
	test_pop_back();
	test_big_three();
	test_erase_small();
    test_erase();
    test_multiple_erase();
    test_insert();
    test_multiple_insert();

    cout << "All List Tests Passed!" << endl;
    return 0;
}

// If you have multiple test cases in this file, define the
// test functions here.

void test_empty() {
	List<int> list;
	assert(list.empty());
	list.push_back(1);
	list.pop_front();
	assert(list.empty());
	list.push_back(1);
	list.push_back(2);
	list.pop_front();
	assert(!list.empty());
	list.pop_front();
	assert(list.empty());
	cout << "test_empty PASS!" << endl;
}

void test_size() {
	List<int> list;
	assert(list.size() == 0);
	list.push_back(1);
	assert(list.size() == 1);
	for (int i = 0; i < 10; ++i) {
		list.push_back(1);
	}
	assert(list.size() == 11);
	cout << "test_size PASS!" << endl;
}

void test_front() {
	List<double> list;
	list.push_back(1.5);
	assert(list.front() == 1.5);
	list.push_front(2.23);
	assert(list.front() == 2.23);
	list.push_back(1.11);
	assert(list.front() == 2.23);
	list.pop_front();
	list.pop_front();
	assert(list.front() == 1.11);
	cout << "test_front PASS!" << endl;
}


void test_back() {
	List<double> list;
	list.push_back(1.5);
	assert(list.back() == 1.5);
	list.push_back(2.23);
	assert(list.back() == 2.23);
	list.push_front(1.11);
	assert(list.back() == 2.23);
	list.pop_back();
	list.pop_back();
	assert(list.back() == 1.11);
	cout << "test_back PASS!" << endl;
}

void test_push_front() {
	List<int> list;
	list.push_front(1);
	assert(list.front() == 1);
	list.push_front(10);
	assert(list.front() == 10);
	list.push_front(100);
	assert(list.front() == 100);
	List<int>::Iterator iter = list.begin();
	assert(*iter == 100);
	cout << "test_push_front PASS!" << endl;
}

void test_push_back() {
	List<int> list;
	list.push_back(1);
	assert(list.back() == 1);
	list.push_back(10);
	assert(list.back() == 10);
	list.push_back(100);
	assert(list.back() == 100);
	List<int>::Iterator iter = list.begin();
	++++iter;
	assert(*iter == 100);
	cout << "test_push_back PASS!" << endl;
}

void test_big_three() {
	List<int> list;
	assert(list.empty() && list.size() == 0);
	List<int> list2;
	list2.push_back(1);
	List<int> list3(list2);
	assert(list3.size() == 1);
	assert(list3.front() == 1);
	list = list3;
	assert(list.size() == 1);
	assert(list.front() == 1);
	list3.~List();
	assert(list3.empty());
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	List<int> list4(list);
	assert(list4.size() == 4 && list4.front() == 1 && list4.back() == 4);
	list2 = list4;
	assert(list2.size() == 4 && list2.front() == 1 && list2.back() == 4);
	list.~List();
	list2.~List();
	list3.~List();
	list4.~List();
	assert(list.empty() && list2.empty() && list3.empty() && list4.empty());

	cout << "test_big_three PASS!" << endl;
}

void test_pop_front() {
	List<int> list;
	list.push_back(1);
	list.pop_front();
	assert(list.empty());
	list.push_back(1);
	list.push_back(2);
	list.pop_front();
	assert(list.front() == 2);
	list.push_back(3);
	list.push_back(4);
	list.pop_front();
	list.pop_front();
	assert(list.front() == 4);
	list.pop_front();
	assert(list.empty());
	cout << "test_pop_front PASS!" << endl;
}

void test_pop_back() {
	List<int> list;
	list.push_back(1);
	list.pop_back();
	assert(list.empty());
	list.push_back(1);
	list.push_back(2);
	list.pop_back();
	assert(list.front() == 1);
	list.pop_front();
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.pop_back();
	list.pop_back();
	assert(list.front() == 3);
	list.pop_back();
	assert(list.empty());
	cout << "test_pop_back PASS!" << endl;
}

void test_erase_small() {
	List<int> list;
	list.push_back(1);
	List<int>::Iterator iter = list.begin();
	list.erase(iter);
	assert(list.empty());
	cout << "test_erase_small PASS!" << endl;
}

void test_erase() {
	List<int> list;
	for (int i = 1; i < 7; i++) {
		list.push_back(i);
	}
	List<int>::Iterator iter = list.begin();
	++iter;
	list.erase(iter);
	list.pop_front();
	assert(list.front() == 3);
	iter = list.begin();
	list.erase(iter);
	assert(list.front() == 4);
	iter = list.begin();
	++++iter;
	list.erase(iter);
	assert(list.back() == 5);
	cout << "test_erase PASS!" << endl;
}

void test_multiple_erase() {
	List<int> list;
	for (int i = 1; i < 7; i++) {
		list.push_back(i);
	}
	List<int>::Iterator iter = list.begin();
	++iter;
	for (int i = 0; i < 3; i++) {
		list.erase(iter);
		iter = list.begin();
	}
	list.pop_front();
	assert(list.front() == 5);
	cout << "test_multiple_erase PASS!" << endl;
}

void test_insert() {
	List<int> list;
	List<int>::Iterator iter = list.begin();
	list.insert(iter, 1);
	assert(list.front() == 1);
	iter = list.begin();
	list.insert(iter, 2);
	assert(list.front() == 2);
	iter = list.begin();
	++iter;
	list.insert(iter, 3);
	list.pop_front();
	assert(list.front() == 3);
	cout << "test_insert PASS!" << endl;
}

void test_multiple_insert() {
	List<int> list;
	List<int>::Iterator iter = list.begin();
	for (int i = 1; i < 9; i++) {
		list.insert(iter, 9 - i);
		iter = list.begin();
	}
	for (int i = 1; i < 9; i++) {
		assert(list.front() == i);
		list.pop_front();
	}
	List<int> list2;
	list2.push_back(9);
	list2.push_back(10);
	iter = list2.begin();
	++iter;
	list2.insert(iter, 1);
	iter = list2.begin();
	++iter;
	list2.insert(iter, 2);
	iter = list2.begin();
	++++iter;
	list2.insert(iter, 3);
	iter = list2.begin();
	++++++iter;
	list2.insert(iter, 4);
	list2.pop_front();
	assert(list2.front() == 2);
	list2.pop_front();
	assert(list2.front() == 3);
	list2.pop_front();
	assert(list2.front() == 4);
	list2.pop_front();
	assert(list2.front() == 1);
	cout << "test_multiple_insert PASS!" << endl;
}