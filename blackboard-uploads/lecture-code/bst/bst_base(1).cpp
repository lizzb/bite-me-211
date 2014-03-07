/**
 Implementation for BST and BSTNode member functions
 See header file or function comments for more details
 */
#include "bst.h"

/**
 Recursive helper function to calculate the number of BSTNodes that are
 descendants of the given BSTNode

 @param node the node whose descendants we want to count
 @return the number of nodes in this subtree

 @author EECS 211, Section 21, Winter 2014
 */
int node_size(BSTNode* node)
{
  int size = 0;
  
  if (node == NULL)
    return 0;

  size += node_size(node->left());
  size++;
  size += node_size(node->right());

  return size;
}

/**
 Constructs an empty tree
 */
BST::BST()
{
  root = NULL;
}

/**
 Creates a deep copy of the given tree
 @param the BST to copy
 */
BST::BST(const BST& copy)
{
  //TODO:  implement the BST copy constructor
}

/**
 Counts the number of nodes in the BST
 @return the number of nodes
 */
int BST::size() const
{
  return node_size(root);
}

/**
 Returns a pointer to the node that contains a given value, or NULL if that
 value is not in the tree

 @param target the value to find
 @return a pointer to the node in the tree that contains that value (or NULL)

 @author EECS 211, Section 21, Winter 2014
 */
BSTNode* BST::find(int target)
{
  BSTNode* node = root;

  while (node != NULL)
  {
    if (node->data < target)
      node = node->right();
    else if (node->data == target)
      return node;
    else //if (node->data > target)
      node = node->left();
  }

  return NULL;
}

/**
 Adds a new value into the tree
 The insertion will fail if the tree already contains the given value

 @param value the value to insert
 @return whether the insertion succeeded
 */
bool BST::insert(int value)
{
  //TODO:  implement insertion
  return false;
}

/**
 Removes a value from the tree
 The removal will fail if the tree does not contain the given value

 @param value the value to remove
 @return whether the removal succeeded
 */
bool BST::remove(int value)
{
  //TODO:  implement removal
  return false;
}

/**
 Returns a vector containing all of the values in the tree in sorted order

 @return a vector containing the sorted values
 */
vector<int> BST::sort() const
{
  vector<int> values;
  
  //TODO:  implement sorting

  return values;
}

/**
 Deconstructs the tree and all of its nodes
 */
BST::~BST()
{
  //TODO:  implement destructor
}

/**
 Constructs a new node with value 0
 */
BSTNode::BSTNode()
{
  //TODO:  implement default constructor
}

/**
 Constructs a new node with the given value
 */
BSTNode::BSTNode(int value)
{
  //TODO:  implement single-value consructor
}

/**
 Returns the left child pointer for the BSTNode
 @return the left child pointer
 */
BSTNode* BSTNode::left()
{
  return lc;
}

/**
 Returns the left child pointer for a const BSTNode
 @return the left child pointer
 */
const BSTNode* BSTNode::left() const
{
  return lc;
}

/**
 Returns the right child pointer for the BSTNode
 @return the right child pointer
 */
BSTNode* BSTNode::right()
{
  return rc;
}

/**
 Returns the right child pointer for a const BSTNode
 @return the right child pointer
 */
const BSTNode* BSTNode::right() const
{
  return rc;
}

/**
 Returns a reference to the data value for the BSTNode
 The data value can be modified by placing this on the LHS of an assignment

 @return a reference to the data value
 */
int& BSTNode::value()
{
  return data;
}

/**
 Returns a copy of the data value in a const BSTNode
 @return the data value
 */
int BSTNode::value() const
{
  return data;
}

/**
 Node destructor
 */
BSTNode::~BSTNode()
{
  //TODO:  implement node destructor
}

/**
 Function to print out a binary search tree to a given output stream

 @param out the output stream
 @param bst the binary search tree
 @return the output stream (after printing)
 */
ostream& operator<<(ostream& out, BST& bst)
{
  return out << bst.root;
}

/**
 Function that recursively prints a node and all of its descendants to the
 given output stream

 @param out the output stream
 @param node the node whose descendants you want to print
 @return the output stream
 */
ostream& operator<<(ostream& out, BSTNode* node)
{
  if (node == NULL)
    return out << "()";
  else if (node->left() == NULL && node->right() == NULL)
    return out << node->data;
  else
    return out << '(' << node->data << ' ' << node->left() << ' ' << node->right() << ')';
}
