/**
 Test driver for LinkedList class
 
 @author William Hendrix
 */
#include <iostream>
using namespace std;

#include "linkedlist.h"

int main()
{
  LinkedList ll;

  //Add 10..1 to list
  for (int i = 10; i > 0; i--)
    ll.push_back(i);
  
  //Test size()
  cout << "The list has " << ll.getSize() << " elements currently." << endl;

  //Add -42 and 42 to ends of array
  ll.insert(-42, 5);
  ll.insert(27, 11);
  ll.insert(42, 0);

  //Change 4th element to -17
  ll[3] = -17;
  
  //Remove 1st element and add 42 in its place
  cout << ll << endl;
  ll.remove(0);
  ll.push_back(42);

  //Print out linked list
  cout << endl << ll << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}