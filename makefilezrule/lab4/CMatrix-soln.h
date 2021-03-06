// matrix.h: interface of the CMatrix class

#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix
{
	int		m_nRow; // # of rows
	int		m_nCol; // # of columns
	double	*m_aData;

public:
	CMatrix(); 	// make a null matrix

	CMatrix(double d);				// 1 by 1 matrix
	CMatrix(int nRow, int nCol);	// nRow by nCol zero matrix
	CMatrix(const char *str);		// matrix from string

	~CMatrix();

	// Is this matrix a null matrix?
	bool IsNull();

	// swap this and m
	void swap(CMatrix &m); 

	void resize(int nRow, int nCol);

	// get
	int	getNRow(); // return # of rows
	int	getNCol(); // return # of columns

	// return the element at i-th row and j-th column
	double &element(int i, int j);
    
    
	//double& operator=(double val);
	//double& operator=(double& newValue);


    CMatrix& operator=(CMatrix& mat);
    //CMatrix& operator=(CMatrix& mat);
    
    // returns the result of adding two matrices;
    // result is a null matrix if input matrices are not the same size
    CMatrix& operator+(CMatrix& mat);

    // returns the result of subtracting one matrix from another;
	// result is a null matrix if input matrices are not the same size
	CMatrix& operator-(CMatrix& mat);

	CMatrix& operator*(CMatrix& mat);

	// returns the result of dividing this matrix by a scalar (1x1 matrix);
	// the result can be a null matrix if mat is not 1x1
	CMatrix& operator/(CMatrix& mat); // should return regular cmatrix or by reference??

	// returns true if the given CMatrix is the same size
	// and contains all of the same values as this matrix (false otherwise)
	bool operator==(CMatrix& mat);


	// returns false if the given CMatrix is the same size
	// and contains all of the same values as this matrix (true otherwise)
	bool operator!=(CMatrix& mat);


	 // output the matrix

}; // class CMatrix

//void printMatrix(CMatrix &m);

/*
 CMatrix& CMatrix::operator=(CMatrix& mat)
 {
 value = val;
 return *this;
 }
 
 CMatrix& CMatrix::operator=(CMatrix& mat)
 {
 value = cvar.value;
 return *this;
 }
 
 CMatrix& CMatrix::operator*()
 {
 return value;
 }
 
 CMatrix CVariable::CMatrix*() const
 {
 return value;
 }
 */



// can i put the overloaded operator here??



#endif // CMATRIX_H