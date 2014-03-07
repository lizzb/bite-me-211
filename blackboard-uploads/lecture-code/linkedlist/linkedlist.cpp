/**
 Class implementation for LinkedList class (singly-linked list)
 The Node class that actually stores the data in the list is defined here, as a "private" class

 @author William Hendrix
 */
#include <assert.h>
#include "linkedlist.h"

/**
 Node class definition
 Nodes store the values in the LinkedList, and their next pointers form the chain for the LinkedList
 Node fields are accessed by LinkedList member functions, almost like a struct
 */
class Node
{
  friend LinkedList;
  friend ostream& operator<<(ostream& out, LinkedList& ll);
private:
  int data;
  Node* next;
public:
  Node(int init_data);
};

/**
 Constructs a Node to store the given int
 
 @param init_data data to store in this Node
 */
Node::Node(int init_data)
{
  data = init_data;
  next = NULL;
}

/**
 Default constructor for LinkedList
 Initializes an empty list
 */
LinkedList::LinkedList()
{
  head = tail = NULL;
  size = 0;
}

/**
 Appends a given integer to the end of the list
 Returns true if the insertion was successful (should always succeed)

 @param data value to append
 @return whether the insertion was successful
 */
bool LinkedList::push_back(int data)
{
  Node* toAdd = new Node(data);
  if (tail == NULL)
  {
    head = toAdd;
  }
  else
  {
    tail->next = toAdd;
  }
  tail = toAdd;
  size++;

  return true;
}

/**
 Inserts the given Node at a specified location
 Will fail if the location is negative or more than one past the end of the list

 @param value the integer to insert
 @param index the location at which to insert the value
 @return whether the insertion was successful
 */
bool LinkedList::insert(int value, int index)
{
  //Check index is valid
  if (index < 0 || index > size)
    return false;

  //Crate Node to insert
  Node* toIns = new Node(value);

  //Change tail of toIns and another Node
  //Find Node at index - 1:
  Node* before = head;

  if (index == 0)
  {
    toIns->next = head;
    head = toIns;
  }
  else
  {
    for (int i = 0; i < index - 1; i++)
      before = before->next;

    Node* after = before->next;
    toIns->next = after;
    before->next = toIns;
  }

  if (index == size)
    tail = toIns;

  size++;
  return true;
}

/**
 Removes an integer from the LinkedList
 Will fail if the index is not a valid index of a Node

 @param index the index of the Node to delete
 @return whether the deletion was successful
 */
bool LinkedList::remove(int index)
{
  if (index < 0 || index >= size)
    return false;

  if (index > 0)
  {
  //Find element before Node to remove
  Node* before = head;

  for (int i = 0; i < index - 1; i++)
    before = before->next;

  Node* victim = before->next;
  before->next = victim->next;
    if (index == size - 1)
    tail = before;
  delete victim;
  }
  else
  {
    Node* victim = head;
    head = head->next;
    delete victim;
  }

  size--;

  return true;
}

/**
 Destructor for LinkedList
 Deletes all of the Nodes in the LinkedList
 */
LinkedList::~LinkedList()
{
  Node* victim = head;
  for (int i = 0; i < size; i++)
  {
    Node* save = victim->next;
    delete victim;
    victim = save;
  }
}

/**
 Access (subscript) operator for LinkedList
 Returns a reference to the int value at the given index
 Because it returns a reference, the return value of this
   function can appear on the LHS of an assignment statement

 @param index the index of the value to return
 @return a reference to the int at that location
 */
int& LinkedList::operator[](int index)
{
  assert(index >= 0);
  assert(index < size);
  Node* temp = head;
  for (int i = 0; i < index; i++)
  {
    temp = temp->next;
  }

  return temp->data;
}

/**
 Returns the size of the LinkedList

 @return the size
 */
int LinkedList::getSize()
{
  return this->size;
}

/**
 Utility function to print the elements of the LinkedList to a given output stream

 @param out the output stream
 @param ll the LinkedList to print
 @return the output stream
 */
ostream& operator<<(ostream& out, LinkedList& ll)
{
  Node* temp = ll.head;

  for (int i = 0; i < ll.size; i++)
  {
    out << temp->data << " ";
    temp = temp->next;
  }

  return out;
}
