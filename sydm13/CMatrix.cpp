#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
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
    if(m_aData!=NULL)
        delete m_aData;


  // i'm having issues with my destructor, i think hence malloc errors
}

void CMatrix::swap(CMatrix &m)
{
	int tmp_i;
	double *tmp_p;

	// swap all the member variables

	tmp_i = m_nCol; m_nCol = m.m_nCol; m.m_nCol = tmp_i;

	tmp_i = m_nRow; m_nRow = m.m_nRow; m.m_nRow = tmp_i;

	tmp_p = m_aData; m_aData = m.m_aData; m.m_aData = tmp_p;
}

bool CMatrix::IsNull() const
{
	return m_aData == 0;
}

void CMatrix::resize(int nRow, int nCol)
{
	// 1 Create a new matrix m.
	// 2 Assign values to m.
	// 3 Make this matrix m by swapping.

	CMatrix m(nRow, nCol);

	for (int i = 0; (i < m_nRow) && (i < m.m_nRow); ++i)
		for (int j = 0; (j < m_nCol) && (j < m.m_nCol); ++j)
			m.element(i, j)  = element(i, j);

	// We don't need assignment here because we don't need m any more!
	swap(m);

	// m's destructor will be called here.
	// The old m_aData will be deleted then.


	// ****** see comments above in this function
	// try to reuse this function body for assignment and operators and stuff
}

int CMatrix::getNRow()
{
	return m_nRow;
}

int CMatrix::getNCol()
{
	return m_nCol;
}

double &CMatrix::element(int i, int j)
{
	assert((i >= 0) && (i < m_nRow));
	assert((j >= 0) && (j < m_nCol));

	return m_aData[i*m_nCol+j];
}

//new stuff-----------------------------------------------------/
CMatrix CMatrix::operator+(CMatrix& mat)
{
    if ((mat.getNRow() != this->getNRow()) || (mat.getNCol() != this->getNCol())) //control for matrices that aren't the same size
    {
        return CMatrix();
    }
    else {
        for (int i = 0; i < mat.getNRow(); ++i)
		{
			std::cout << "\t";
			for (int j = 0; j < mat.getNCol(); ++j)
            {
				//std::cout << m.element(i, j) << "\t";
                this->element(i, j) = this->element(i, j) + mat.element(i, j);
                std::cout << this->element(i, j) << "\t";
			//std::cout << std::endl;
            }
            std::cout << std::endl;
		}
        return *this;
    }
}

CMatrix CMatrix::operator-(CMatrix& mat)
{
    if ((mat.getNRow() != this->getNRow()) || (mat.getNCol() != this->getNCol())) //control for matrices that aren't the same size
    {
        return CMatrix();
    }
    else {
        for (int i = 0; i < mat.getNRow(); ++i)
		{

            std::cout << "\t";
			for (int j = 0; j < mat.getNCol(); ++j)
            {
				//std::cout << m.element(i, j) << "\t";
                this->element(i, j) = this->element(i, j) - mat.element(i, j);
                std::cout << this->element(i, j) << "\t";
                //std::cout << std::endl;
            }
            std::cout << std::endl;
		}
        return *this;
    }
}

CMatrix CMatrix::operator*(CMatrix& mat)
{
    /* if ((mat.getNRow() != this->getNRow()) || (mat.getNCol() != this->getNCol())) //control for matrices that aren't the same size
    {
        return CMatrix();
    } */
    
    if (((mat.getNRow() == 1) && (mat.getNCol() == 1)) || ((this->getNRow() == 1) && (this->getNCol() == 1))) //at least one of the matrices needs to be 1x1, but in this case, neither is
    {
        if ((mat.getNRow() == 1) && (mat.getNCol() == 1))
        {
            for (int i = 0; i < this->getNRow(); ++i)
            {
                //std::cout << std::endl;
                std::cout << "\t";
                for (int j = 0; j < this->getNCol(); ++j)
                {
                    //std::cout << m.element(i, j) << "\t";
                    this->element(i, j) = this->element(i, j) * mat.element(0, 0);
                    std::cout << this->element(i, j) << "\t";
                }
                std::cout << std::endl;
            }
            return *this;
        }
        else if ((this->getNRow() == 1) && (this->getNCol() == 1))
        {
            for (int i = 0; i < mat.getNRow(); ++i)
            {
                //std::cout << std::endl;
                std::cout << "\t";
                for (int j = 0; j < mat.getNCol(); ++j)
                {
                    //std::cout << m.element(i, j) << "\t";
                    mat.element(i, j) = mat.element(i, j) * this->element(0, 0);
                    std::cout << mat.element(i, j) << "\t";
                    //std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            return mat;
        }
        else {
            return CMatrix(); // return a null matrix
        }
    }
    else {
        return CMatrix(); // return a null matrix
    }
}

CMatrix CMatrix::operator/(CMatrix& mat)
{
	// check that given parameter is a scalar (a 1x1 matrix)
    if ((mat.getNCol() != 1) && (mat.getNRow() != 1))
    {
        return CMatrix();
    }
    else {
        for (int i = 0; i < this->getNRow(); ++i)
        {
            //std::cout << std::endl;
            std::cout << "\t";
            for (int j = 0; j < this->getNCol(); ++j)
            {
                //std::cout << m.element(i, j) << "\t";
                this->element(i, j) = this->element(i, j) / mat.element(0, 0);
                std::cout << this->element(i, j) << "\t";
                //std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        return *this;
    }
}

bool CMatrix::operator==(CMatrix& mat)
{
    int error = 0;
    if ((mat.getNRow() == this->getNRow()) && (mat.getNCol() == this->getNCol()))
    {
        for (int i = 0; i < this->getNRow(); ++i)
        {
            std::cout << "\t";
            for (int j = 0; j < this->getNCol(); ++j)
            {
                //std::cout << m.element(i, j) << "\t";
                /* this->element(i, j) = this->element(i, j) / mat.element(0, 0);
                std::cout << this->element(i, j) << "\t";
                std::cout << std::endl;
                 */
                if (this->element(i,j) != mat.element(i, j))
                {
                    error = 1;
                }
            }
        }
        if (error != 0)
        {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

// no need to loop through again - just return the opposite of == for !=
// or vice versa
bool CMatrix::operator!=(CMatrix& mat)
{
    int error = 0;
    if ((mat.getNRow() == this->getNRow()) && (mat.getNCol() == this->getNCol()))
    {
        for (int i = 0; i < this->getNRow(); ++i)
        {
            std::cout << "\t";
            for (int j = 0; j < this->getNCol(); ++j)
            {
                //std::cout << m.element(i, j) << "\t";
                /* this->element(i, j) = this->element(i, j) / mat.element(0, 0);
                 std::cout << this->element(i, j) << "\t";
                 std::cout << std::endl;
                 */
                if (this->element(i,j) != mat.element(i, j))
                {
                    error = 1;
                }
            }
        }
        if (error != 0)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
}

//end new stuff------------------------------------------------/

// don't need this anymore, now that you overloaded the << operator
void printMatrix(CMatrix &m)
{
	if (m.IsNull())
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

/* std::ostream& operator<<(std::ostream& out, CMatrix& mat)
{
    if (mat.IsNull())
		out << "\tnull matrix" << std::endl;
	else
	{
		// row by row
		for (int i = 0; i < mat.getNRow(); ++i)
		{
			out << "\t";
			for (int j = 0; j < mat.getNCol(); ++j)
				out << mat.element(i, j) << "\t";
			out << std::endl;
		}
	}
	out << std::endl;
    return out;
} */

const CMatrix& CMatrix::operator=(const CMatrix& m)
{
    m_nRow=m.m_nRow;
    m_nCol=m.m_nCol;
    
    double *temp;
    temp=new double[m_nRow*m_nCol];
    for(int i=0;i<m_nRow*m_nCol;i++)
    {
        temp[i]=m.m_aData[i];
    }
    if(m_aData!=NULL)
        delete(m_aData);
    m_aData=temp;
    return *this;
}
