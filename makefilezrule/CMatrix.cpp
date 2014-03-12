#include <iostream>
#include <string.h>
#include <assert.h>

#include "CMatrix.h"

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
	else return ERR;
}

// Checks if the rows and columns are valid based on input
// returns true if matrix is a valid size, otherwise false.....?
bool GetRowCol(const char *str, int &nRow, int &nCol)
{
	nRow = 0;
	nCol = 0;

	// should start with a '['
	if (str[0] != '[') return false;

	char piece[100];
	int col = 0, st = 1;
	for (;;) // ?????
	switch (MatrixPiece(str, st, piece))
	{
		// new row
		case SEP: 
			if ((nRow != 0) && (col != nCol))
				return false;
			nCol = col;
			++nRow;
			col = 0;
			break;
		// new number
		case NUM: 
			++col;
			break;
		case END:
			if ((nRow != 0) && (col != nCol))
				return false;
			nCol = col;
			++nRow;
			return true;
		case ERR: return false;
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
		case SEP: break;
		case NUM:
			array[i] = atof(piece);
			++i;
			break;
		case END: return;
		case ERR: assert(false);
		default:
			assert(false);
	}
}

CMatrix::CMatrix(): m_nRow(0), m_nCol(0), m_aData(0)
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

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
CMatrix::CMatrix(const char *str)
	: m_nRow(0), m_nCol(0), m_aData(0)
{
	int nRow, nCol;
	if (!GetRowCol(str, nRow, nCol)) return;

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
 Name:     swap
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
 Name:     resize
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

	for (int i = 0; (i < getNRow()) && (i < m.getNRow()); ++i)
		for (int j = 0; (j < getNCol()) && (j < m.getNCol()); ++j)
			m.element(i, j)  = element(i, j);

	// We don't need assignment here because we don't need m any more!
	swap(m);

	// m's destructor will be called here.
	// The old m_aData will be deleted then.
}

bool CMatrix::isNull() { return m_aData == 0; }

int CMatrix::getNRow() { return m_nRow; }
int CMatrix::getNCol() { return m_nCol; }

/* ----------------------------------------------------------------------------
 Name:     element
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
 Name:     printMatrix
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- 
void printMatrix(CMatrix &m)
{
	if (m.isNull())
		std::cout << "\tnull matrix" << std::endl;
	else
	{
		// row by row
		for (int i = 0; i < m.getNRow(); ++i)
		{
			std::cout << "\t";
			for (int j = 0; j < m.getNCol(); ++j)
				std::cout << m.element(i, j) << "\t";
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
*/