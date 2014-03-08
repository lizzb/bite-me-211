/* ----------------------------------------------------------------------------

cmatrix.cpp

Extended CMatrix class (based off Lab 4 provided solution)

Handles matrix addition and subtraction, scalar multiplication, 
and equality and inequality operators.

---------------------------------------------------------------------------- */
#include <iostream>
#include <string.h>
#include <assert.h>

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
  // only matrices of the same size can be added/subtracted


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



// for string input, we get something from previous projects
enum MATRIX_INPUT {NUM, SEP, END, ERR};

MATRIX_INPUT MatrixPiece(const char *buffer, int &st, char *piece)
{
	while (buffer[st] == ' ')
		st++;
    
	if (((buffer[st] <= '9') && (buffer[st] >= '0')) || (buffer[st] == '.'))
	{
		int ed = st;
		while (((buffer[ed] <= '9') && (buffer[ed] >= '0')) || (buffer[ed] == '.'))
		{
			piece[ed-st] = buffer[ed];
			ed++;
		}
		piece[ed-st] = 0;
		st = ed;
		return NUM;
	}
	else if (buffer[st] == ']')
	{
		++st;
		return END;
	}
	else if (buffer[st] == ';')
	{
		++st;
		return SEP;
	}
	else
		return ERR;
}

bool GetRowCol(const char *str, int &nRow, int &nCol)
{
	nRow = 0;
	nCol = 0;
    
	// should start with a '['
	if (str[0] != '[')
		return false;
    
	char piece[100];
	int col = 0, st = 1;
	for (;;)
        switch (MatrixPiece(str, st, piece))
	{
		case SEP: // new row
			if ((nRow != 0) && (col != nCol))
				return false;
			nCol = col;
			++nRow;
			col = 0;
			break;
		case NUM: // new number
			++col;
			break;
		case END:
			if ((nRow != 0) && (col != nCol))
				return false;
			nCol = col;
			++nRow;
			return true;
		case ERR:
			return false;
		default:
			return false;
	}
	return false;
}

void FillArray(const char *str, double *array, int size)
{
	// call GetRowCol first, this one should not fail
    
	char piece[100];
	int i = 0, st = 1;
	for (; i < size;)
		switch (MatrixPiece(str, st, piece))
	{
		case SEP:
			break;
		case NUM:
			array[i] = atof(piece);
			++i;
			break;
		case END:
			return;
		case ERR:
			assert(false);
		default:
			assert(false);
	}
}

CMatrix::CMatrix()
: m_nRow(0), m_nCol(0), m_aData(0)
{
}

CMatrix::CMatrix(double d)
: m_nRow(1), m_nCol(1), m_aData(new double[1])
{
	element(0, 0) = d;
}

CMatrix::CMatrix(int nRow, int nCol)
: m_nRow(nRow), m_nCol(nCol), m_aData(new double[nRow*nCol])
{
	for (int i = 0; i < m_nRow; ++i)
		for (int j = 0; j < m_nCol; ++j)
			element(i, j) = 0;
}

CMatrix::CMatrix(const char *str)
: m_nRow(0), m_nCol(0), m_aData(0)
{
	int nRow, nCol;
	if (!GetRowCol(str, nRow, nCol))
		return;
    
	m_nRow = nRow;
	m_nCol = nCol;
	m_aData = new double[m_nRow*m_nCol];
    
	FillArray(str, m_aData, m_nRow*m_nCol);
	// FillArray should not return false since we checked that with GetRowCol
}

CMatrix::~CMatrix()
{
	delete[] m_aData;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void CMatrix::swap(CMatrix &m)
{
	int tmp_i;
	double *tmp_p;
    
	// swap all the member variables
    
	tmp_i = m_nCol; m_nCol = m.m_nCol; m.m_nCol = tmp_i;
    
	tmp_i = m_nRow; m_nRow = m.m_nRow; m.m_nRow = tmp_i;
    
	tmp_p = m_aData; m_aData = m.m_aData; m.m_aData = tmp_p;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
bool CMatrix::IsNull()
{
	return m_aData == 0;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void CMatrix::resize(int nRow, int nCol)
{
	// 1 Create a new matrix m.
	// 2 Assign values to m.
	// 3 Make this matrix m by swapping.
    
	CMatrix m(nRow, nCol);
    
	for (int i = 0; (i < NRow()) && (i < m.NRow()); ++i)
		for (int j = 0; (j < NCol()) && (j < m.NCol()); ++j)
			m.element(i, j)  = element(i, j);
    
	// We don't need assignment here because we don't need m any more!
	swap(m);
    
	// m's destructor will be called here.
	// The old m_aData will be deleted then.
}

int CMatrix::NRow()
{
	return m_nRow;
}

int CMatrix::NCol()
{
	return m_nCol;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
double &CMatrix::element(int i, int j)
{
	assert((i >= 0) && (i < m_nRow));
	assert((j >= 0) && (j < m_nCol));
    
	return m_aData[i*m_nCol+j];
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void PrintMatrix(CMatrix &m)
{
	if (m.IsNull())
		std::cout << "\tnull matrix" << std::endl;
	else
	{
		// row by row
		for (int i = 0; i < m.NRow(); ++i)
		{
			std::cout << "\t";
			for (int j = 0; j < m.NCol(); ++j)
				std::cout << m.element(i, j) << "\t";
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
