// matrix.h: interface of the CMatrix class

#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix
{
	int	m_nRow; // # of rows
	int	m_nCol; // # of columns
	double* m_aData;

public:
	CMatrix(); // make a null matrix
	CMatrix(double d); // 1 by 1 matrix
	CMatrix(int nRow, int nCol); // nRow by nCol zero matrix
	CMatrix(char *str); // matrix from string
	~CMatrix();

	bool isNull();

	void swap(CMatrix& m); // swap this and m

	void resize(int nRow, int nCol);

	// get
	int	getNRow(); // return # of rows
	int	getNCol(); // return # of columns

	// return the element at i-th row and j-th column
	double& element(int i, int j);
}; // class CMatrix

void printMatrix(CMatrix& m); 

#endif // CMATRIX_H