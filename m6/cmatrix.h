/* ----------------------------------------------------------------------------

cmatrix.cpp + cmatrix.h 	-	Define the CMatrix class

---
cmatrix.h


Based off ... some lab solution i'm assuming....

Extended CMatrix class 
handle matrix addition and subtraction, scalar multiplication, 
and equality and inequality operators.

---------------------------------------------------------------------------- */


using namespace std;

// Returns the result of adding two matrices;
// Result is a null matrix if input matrices are not the same size
CMatrix operator+(CMatrix& mat);

// Returns the result of subtracting one matrix from another;
// result is a null matrix if input matrices are not the same size
CMatrix operator-(CMatrix& mat);

// Returns the result of multiplying this matrix by another matrix;
// the result can be a null matrix if
// neither this nor the given matrix are 1x1
CMatrix operator*(CMatrix& mat);

// Returns the result of dividing this matrix by a scalar (1x1 matrix)
// result can be a null matrix if mat is not 1x1
CMatrix operator/(CMatrix& mat); 


// Returns true if the given CMatrix is the same size
// and contains all of the same values as this matrix
// (false otherwise) 
bool operator==(CMatrix& mat);


// Returns false if the given CMatrix is the same size
// and contains all of the same values as this matrix
// (true otherwise) 
bool operator!=(CMatrix& mat);