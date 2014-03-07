/**
 Class definition for LinkedList class
 Stores and manipulates a singly-linked list of ints
 Implements main LinkedList operations, including access, insertion, and deletion

 @author William Hendrix
 */

#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include <iostream>
using namespace std;

/**
  LinkedList and Node class
    Store int data
    friends
    Node members:  data, next
    Node constructor
    List members:  head, tail, size
  LinkedList implementation (4 phases)
    Default constructor
    Print method (ostream& ...)
    push_back(int)
  *Test*
    Destructor
    size()
    Access (operator[])
  *Test*
    Insert
  *Test*
    Delete
  *Test*
  Doubly-linked list
    Add prev to Node
    Update push_back, insert, delete, access
  Optional
    Copy constructor
    Assignment operator
    Concatenation (+)
 */

//Define class Node inside linkedlist.cpp ("private" class)
class Node;

//Define LinkedList class
class LinkedList
{
  friend ostream& operator<<(ostream& out, LinkedList& ll);
private:
  int size;
  Node* head;
  Node* tail;
public:
  LinkedList();
  bool push_back(int value);
  bool insert(int value, int index);
  bool remove(int index);
  int& operator[](int index);
  int getSize();
  ~LinkedList();
};

ostream& operator<<(ostream& out, LinkedList& ll);

#endif