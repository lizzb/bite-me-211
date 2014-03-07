/**
 Implementations for Complex class member functions
  The Complex class is described in complex.h.

  @author William Hendrix
 */

#include <cmath>
#include "complex.h"

/**
 Default constructor:  constructs the complex number 0 + 0i
 */
Complex::Complex()
{
  re = im = 0.0;
}

/**
 Given a and b, constructs the complex number a + bi

 @param real the real part of the desired complex number
 @param imaginary the imaginary part of the number
 */
Complex::Complex(double real, double imaginary)
{
  re = real;
  im = imaginary;
}

/**
 Copy constructor for Complex objects
 Not strictly necessary, as the default copy constructor would have been sufficient
 When #define DEBUG is uncommented in complex.h, prints out a message to indicate
 when copy constructor is being called.  
 Argument is not modified, so we declare it const.

 @param copy the Complex object to copy
 */
Complex::Complex(const Complex& copy)
{
  //We can access copy.re and .im directly because this constructor is in the Complex:: scope
  re = copy.re;
  im = copy.im;

#ifdef DEBUG
  cout << endl << "Copying ";
  copy.print();
  cout << endl;
#endif
}

/**
 Multiplies this complex number by another and returns the result
 Does not mutate this Complex number, so we declare it const
 (We could also declare it's parameter as const.)

 @param other the Complex number to multiply this one by
 
 @return the product of this Complex number with another
 */
Complex Complex::mult(Complex& other) const
{
  //We can access and modify the private fields of result and other because this function has the correct scope
  Complex result;
  result.re = re * other.re - im * other.im;
  result.im = im * other.re + re * other.im;
  return result;
}

/**
 Adds this complex number to another and returns the result

 @param other the Complex number to add to this one

 @return the sum of the two
 */
Complex Complex::add(Complex& other) const
{
  //Return an anonymous object
  return Complex(re + other.re, im + other.im);
}

/**
 Prints this Complex number to cout
 */
void Complex::print() const
{
  if (fabs(re) > EPSILON || fabs(im) < EPSILON) //re != 0 || im == 0
  {
    cout << re;
    if (im > EPSILON) //im > 0
      cout << " + " << im << 'i';
    else if (im < -EPSILON) //im < 0
      cout << " - " << -im << 'i';
  }
  else //re == 0 && im != 0
    cout << im << 'i';
}

/**
 Calculates and returns the norm (magnitude) of the Complex number, defined by
 |a + bi| = sqrt(a^2 + b^2)

 @return the norm of this Complex number
 */
double Complex::norm() const
{
  return sqrt(re * re + im * im);
}

/**
 Complex destructor
 If #define DEBUG is uncommented in complex.h, will print a message to cout
 every time it's invoked
 */
Complex::~Complex()
{
#ifdef DEBUG
  cout << endl << "Destroying ";
  print();
  cout << endl;
#endif
}
