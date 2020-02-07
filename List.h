#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 5
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //MODIFIES: this
  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //MODIFIES: this
  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: this, may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: this, may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
  List() : first(0), last(0) {};

  // Copy Constructor
  List(const List & other) {
    first = 0;
    last = 0;
    copy_all(other);
  }

  // Copy assignment operator
  List& operator=(const List & rhs) {
    if (this == &rhs) {
      return *this;
    }
    pop_all();
    copy_all(rhs);
    return *this;
  }

  // Destructor
  ~List() {
    pop_all();
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  //MODIFIES: this, may invalidate list iterators
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *first;   // points to first Node in list, or 0 if list is empty
  Node *last;    // points to last Node in list, or 0 if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user

    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.

    Iterator() {
       node_ptr = 0;
    }

    Iterator& operator--() {
      //assert(node_ptr != nullptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
      //assert(node_ptr != nullptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T & operator*() const {
      //assert(node_ptr != nullptr);
      return node_ptr->datum;
    }

    bool operator==(Iterator rhs) const {
      return (node_ptr == rhs.node_ptr);
    }

    bool operator!=(Iterator rhs) const {
      return !(node_ptr == rhs.node_ptr);
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) {
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: this, may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    assert(i != nullptr);
    if(size() == 1) {
      pop_all();
    }
    else if(i == first) {
      pop_front();
    }
    else if(i == last) {
      pop_back();
    }
    else {
      i.node_ptr->next->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = i.node_ptr->next;
      delete i.node_ptr;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (empty()) {
      push_front(datum);
    }
    else if (i == first) {
      push_front(datum);
    }
    else if (i == end()) {
      push_back(datum);
    }
    else {
      Node *new_node = new Node;
      new_node->datum = datum;
      new_node->next = i.node_ptr;
      i.node_ptr->prev->next = new_node;
      new_node->prev = i.node_ptr->prev;
      i.node_ptr->prev = new_node;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

template<class T>
bool List<T>::empty() const {
  return (first == 0);
}

template<class T>
int List<T>::size() const {
  if (empty()) {
    return 0;
  }
  else {
    int size = 0;
    for(Node* ptr = first; ptr; ptr = ptr->next) {
      size++;
    }
    return size;
  }
}

template<class T>
T & List<T>::front() {
  assert(!empty());
  return first->datum;
}

template<class T>
T & List<T>::back() {
  assert(!empty());
  return last->datum;
}

template<class T>
void List<T>::push_front(const T &datum) {

  Node *new_first = new Node();
  new_first->datum = datum;
  if (empty()) {
    new_first->prev = 0;
    new_first->next = 0;
    first = new_first;
    last = new_first;
  }
  else {
    new_first->next = first;
    new_first->prev = 0;
    first->prev = new_first;
    first = new_first;
  }
  return;
}

template<class T>
void List<T>::push_back(const T &datum) {
  Node *new_back = new Node();
  new_back->datum = datum;

  if (empty()) {
    new_back->prev = 0;
    new_back->next = 0;
    last = new_back;
    first = new_back;
  }
  else {
    new_back->prev = last;
    new_back->next = 0;
    last->next = new_back;
    last = new_back;
  }
  return;
}

template<class T>
void List<T>::pop_front() {
  if (size() == 1) {
    delete first;
    last = 0;
    first = 0;
  }
  else {
    Node *current = first;

    first = first->next;
    first->prev = 0;
    delete current;
    current = 0;
  }
  return;
}

template<class T>
void List<T>::pop_back() {
  if (size() == 1) {
    delete first;
    last = 0;
    first = 0;
  }
  else {
    Node *current = last;

    last = last->prev;
    last->next = 0;
    delete current;
    current = 0;
  }

  return;
}

template<class T>
void List<T>::copy_all(const List<T> &other) {
  if (!other.empty()) {
    for (Iterator i(other.first); i.node_ptr != 0; ++i) {
      push_back(i.node_ptr->datum);
    }
  }

  return;
}

template<class T>
void List<T>::pop_all() {
  while(!empty())
  {
    pop_front();
  }

  return;
}


#endif