/**
 Test driver for BST (Binary Search Tree) class
 Tests default constructor, output, insertion, removal, find, and sort methods

 @author William Hendrix
 */
#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
  //Test default constructor
  BST bst;
  cout << "New tree: " << bst << endl;

  //Test insertion
  bst.insert(15);
  bst.insert(10);
  bst.insert(23);
  bst.insert(2);
  bst.insert(12);
  bst.insert(16);
  bst.insert(25);
  cout << "Added 7 elements:  " << bst << endl;

  //Test removal
  bst.remove(25);
  cout << "Removed 12: " << bst << endl;

  //Test bad insertion and removal
  bst.insert(12);
  cout << "Bad removal: " << bst << endl;
  bst.remove(25);
  cout << "Bad insertion: " << bst << endl;

  //Test find
  BSTNode* node = bst.find(10);
  cout << "Subtree rooted at node 10: " << node << endl;

  //Test sort
  vector<int> arr = bst.sort();
  cout << "Sorted elements: ";
  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << ' ';
  cout << endl;

  //End program
  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}
