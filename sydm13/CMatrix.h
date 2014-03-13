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

	CMatrix(double d); // 1 by 1 matrix
	CMatrix(int nRow, int nCol); // nRow by nCol zero matrix

	CMatrix(const char *str); // matrix from string

	~CMatrix();

	// Is this matrix a null matrix?
	bool IsNull() const;
    
    CMatrix operator+(CMatrix& mat); //adding two matrices, NULL result if diff sizes
    CMatrix operator-(CMatrix& mat); //subtracting matrices, NULL matrix if diff sizes
    CMatrix operator*(CMatrix& mat); //multiplying matrices, NULL if at least one isn't just a one by one matrix UNLESS DOING BONUS CREDIT
    const CMatrix& operator=(const CMatrix& m);
    CMatrix operator/(CMatrix& mat); //dividing matrix by a scalar, NULL if mat is not just a 1 by 1 matrix
    bool operator==(CMatrix& mat); //true if CMatrix is same size matrix with all the same values as this matrix, false if not to either or both of those things
    bool operator!=(CMatrix& mat); //same as == overload but true if not same in at least one of two regards and false if same in both regards

	void swap(CMatrix &m); // swap this and m

	void resize(int nRow, int nCol);

	// get
	int	getNRow(); // return # of rows
	int	getNCol(); // return # of columns

	// return the element at i-th row and j-th column
	double &element(int i, int j);

	 // output the matrix

}; // class CMatrix

void printMatrix(CMatrix &m); 

#endif // CMATRIX_H