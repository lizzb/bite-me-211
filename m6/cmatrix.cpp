/* ----------------------------------------------------------------------------

cmatrix.cpp + cmatrix.h

Define the CMatrix class

---
cmatrix.cpp


Based off ... some lab solution i'm assuming....

Extended CMatrix class 
handle matrix addition and subtraction, scalar multiplication, 
and equality and inequality operators.

---------------------------------------------------------------------------- */

#include "cmatrix.h"
using namespace std;

// Return result of adding two matrices
// null if input matrices are not the same size
CMatrix CMatrix::operator+(CMatrix& otherMatrix)
{
  // only matrices of the same size can be added/subtracted


  // if input matrices are not the same size,
  // result is a null matrix 
  return null;
}


// Returns result of subtracting one matrix from another
// null if input matrices are not the same size
CMatrix CMatrix::operator-(CMatrix& otherMatrix)
{
  // Can only add/subtract matrices of the same size
  //only matrices of the same size can be added/subtracted


  // if input matrices are not the same size,
  // result is a null matrix 
  return null;
}


// Return result of multiplying this matrix by a scalar
// null if neither matrix is a scalar (a 1x1 matrix)
CMatrix CMatrix::operator*(CMatrix& otherMatrix)
{
  return null;
}


// Return result of dividing this matrix by a scalar
// null if given matrix is not a scalar (a 1x1 matrix)
CMatrix CMatrix::operator/(CMatrix& otherMatrix)
{

  return null;
}


// Returns true if the given CMatrix is the same size
// and contains all of the same values as this matrix
// (false otherwise) 
bool CMatrix::operator==(CMatrix& otherMatrix)
{
  // check that matrices are same size first
  // if not, return false
  // check that every value is the same in each
  // if any value is not the same, return false
}


// Returns false if the given CMatrix is the same size
// and contains all of the same values as this matrix
// (true otherwise) 
bool CMatrix::operator!=(CMatrix& otherMatrix)
{
  // return the opposite of the == operator
}
