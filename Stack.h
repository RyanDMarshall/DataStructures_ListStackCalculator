#ifndef STACK_H
#define STACK_H
/* Stack.h
 *
 * a templated stack based on a linked list
 * EECS 280 Project 5
 */

#include "List.h"
#include <cstddef>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE CLASS'S PUBLIC INTERFACE OR PRIVATE VARIABLES.
template <typename T>
class Stack {
  // OVERVIEW: a templated, linked-list-based stack
  // The T is type of value stored, and it must implement operator<<

 public:
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy stacks.

  //EFFECTS:  returns true if the stack is empty
  bool empty() const {

    return list.empty();
  }

  //EFFECTS: returns the number of elements in this Stack
  int size() const {

    return list.size();
  }

  //REQUIRES: stack is non-empty. Assert false if it is empty.
  //MODIFIES: this
  //EFFECTS:  removes the item at the top and returns it.
  // Example:
  //    my_stack.push(42);
  //    int value = my_stack.pop();
  //    // At this point in the example, value == 42 and my_stack contains
  //    // exactly the same elements as it did before we
  //    // called my_stack.push(42)
  //    // (i.e., the 42 that we pushed is not on the stack anymore)
  T pop() {

    assert(!empty());

    T front = list.front();
    list.pop_front();

    return front;
  }

  //REQUIRES: stack is non-empty. Assert false if it is empty.
  //EFFECTS:  returns the top element from the stack by reference without
  // popping it.
  // Note: Since the element is returned by reference, the caller can
  // use the call to change the top without doing a pop/push. You
  // should test for that/89 in your tests.
  // Example:
  //    my_stack.push(42);
  //    int value = my_stack.top();
  //    // At this point in the example, value == 42 but my_stack
  //    // *still has the 42 we pushed as it's top element.*
  T & top() {

    assert(!empty());

    return list.front();
  }

  //MODIFIES: this
  //EFFECTS: pushes an item onto the top of the stack
  void push(const T &item) {

    list.push_front(item);

    return;
  }

  //EFFECTS: returns the number of elements in the stack for which
  //  pred(datum) is true, where datum is the value stored in the stack's
  //  elements.  We use a template for the Predicate type so that pred can
  //  either be a functor or a function pointer.
  // E.g., count_if(pred) is 0 for an empty stack. For a non-empty stack,
  // say S.push(item), where item is pushed on a stack S, count_if(pred) will be
  // the sum of S.count_if(pred) and either 1 or 0 depending on
  // whether item satisfies pred, respectively.
  template <typename Predicate>
  int count_if(Predicate pred) const {

    int count = 0;
    typename List<T>::Iterator iter = list.begin();
    while(iter != list.end()) {
      if(pred(*iter)) {
        ++count;
      }
      ++iter;
    }    

    return count;
  }

  //MODIFIES: os
  //EFFECTS: prints all the elements of the stack to os, starting from
  // the top element. Each element printed is followed by a space,
  // including the last element. Do not print a newline.
  // If the stack is empty, print nothing.
  void print(std::ostream &os) const {

    typename List<T>::Iterator iter = list.begin();
    while(iter != list.end()) {
      os << *iter << " ";
      ++iter;
    }
    return;
  }

private:
  /* You must make use of List's interface to implement the stack.
   * You must not make changes to the private section.
   */
  List<T> list;
};


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface, although you
// may add the Big Three if needed.


//MODIFIES: os
//EFFECTS: prints all the elements of the stack to os, starting from
// the top element. Each element printed is followed by a space,
// including the last element. Do not print a newline. If the stack is
// empty, print nothing. Returns os.
template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {

  stack.print(os);

  return os;
}

#endif /* STACK_H */