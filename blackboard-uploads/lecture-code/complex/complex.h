/**
 Header file for Complex class

 Complex objects represent complex numbers, having both a real and imaginary component.
 Objects of the Complex class can be added and multiplied together, and can print 
 themselves and their norms.

 @author William Hendrix
 */

#ifndef __COMPLEX_H
#define __COMPLEX_H

#include <iostream>
using namespace std;

//Uncomment the following line to see when the destructor and copy constructor are being called
//#define DEBUG
//Also, try changing add and mult to accept Complex rather than Complex& arguments

#define EPSILON 1e-13

class Complex
{
private:
  double re;
  double im;
public:
  Complex();
  Complex(double real, double imaginary);
  Complex(const Complex& copy);
  Complex mult(Complex& other) const;
  Complex add(Complex& other) const;
  double norm() const;
  void print() const;
  virtual ~Complex();
};

#endif