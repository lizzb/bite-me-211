/**
 Class definition for Binary Search Tree (BST) class and the nodes that comprise the tree (BSTNode)
 
 This class should support size queries, searching, inserting, removal, element sorting, and printing.
 */
#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <vector>
using namespace std;

class BST;

class BSTNode
{
  friend BST;
  friend ostream& operator<<(ostream& out, BSTNode* node);
private:
  int data;
  BSTNode* lc;
  BSTNode* rc;
public:
  BSTNode();
  BSTNode(int value);
  int& value();
  int value() const;
  BSTNode* left();
  const BSTNode* left() const;
  BSTNode* right();
  const BSTNode* right() const;
  virtual ~BSTNode();
};

class BST
{
  friend ostream& operator<<(ostream& out, BST& bst);
private:
  BSTNode* root;
public:
  BST();
  BST(const BST& copy);
  int size() const;
  BSTNode* find(int target);
  bool insert(int value);
  bool remove(int value);
  vector<int> sort() const;
  virtual ~BST();
};

ostream& operator<<(ostream& out, BST& bst);
ostream& operator<<(ostream& out, BSTNode* node);

#endif
