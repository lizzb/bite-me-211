/**
 Test driver for the Complex class defined in complex.cpp and complex.h

 @author William Hendrix
 */
#include <iostream>
#include "complex.h"
using namespace std;

int main()
{
  //Construct two Complex numbers
  Complex c1(3, 4), c2(3, -4);

  //Test printing and multiplication
  c1.print();
  cout << " times ";
  c2.print();
  cout << " equals ";
  c1.mult(c2).print(); //c1.mult(c2) is a Complex object
  cout << endl;

  //Test addition
  c2.print();
  cout << " plus ";
  c1.print();
  cout << " equals ";
  c2.add(c1).print();
  cout << endl;

  //Test the norm function
  cout << '|';
  c2.print();
  cout << "| = " << c2.norm() << endl;

  //Clean up and exit
  //No delete statements are required because c1 and c2 are local variables
  //(Their destructors will be called automatically.)
  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}
