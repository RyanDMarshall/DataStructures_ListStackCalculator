# Makefile for EECS 280 Project 5

debug_or_optimize = -O1

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 $(debug_or_optimize)

list_test_srcs = $(wildcard List_test_*.cpp)
list_test_exes = $(list_test_srcs:.cpp=.exe)
stack_test_srcs = $(wildcard Stack_test_*.cpp)
stack_test_exes = $(stack_test_srcs:.cpp=.exe)

all: test

debug: debug_or_optimize=-g
debug: test

test: calc List_tests List_compile_check Stack_compile_check Stack_tests
	./List_compile_check ./Stack_compile_check

	./calc < calc_test00.in > calc_test00.out
	diff -q calc_test00.out calc_test00.out.correct

	./calc < calc_test01.in > calc_test01.out
	diff -q calc_test01.out calc_test01.out.correct

List_tests: $(list_test_exes)
	python run_my_tests.py List

Stack_tests: $(stack_test_exes)
	python run_my_tests.py Stack

calc: calc.cpp List.h Stack.h
	$(CXX) $(CXXFLAGS) calc.cpp -o $@

List_test_%.exe: List_test_%.cpp List.h
	$(CXX) $(CXXFLAGS) List_test_$*.cpp -o $@

List_compile_check: List_compile_check.cpp List.h
	$(CXX) $(CXXFLAGS) List_compile_check.cpp -o $@

Stack_compile_check: Stack_compile_check.cpp Stack.h
	$(CXX) $(CXXFLAGS) Stack_compile_check.cpp -o $@

Stack_test_%.exe: Stack_test_%.cpp List.h Stack.h
	$(CXX) $(CXXFLAGS) Stack_test_$*.cpp -o $@

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean :
	rm -vrf *.o *.exe *.gch *.dSYM *.out calc List_compile_check Stack_compile_check
