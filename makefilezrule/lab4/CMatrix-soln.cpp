#include <iostream>
#include <string.h>
#include <assert.h>

#include "CMatrix-soln.h"

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
	//if(*m_aData != NULL || m_aData != NULL)
		delete[] m_aData;
	//else delete m_aData;
	//if(m_aData != NULL) delete[] m_aData; // compiler does nOT like this line
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

bool CMatrix::IsNull()
{
	return m_aData == 0;
}

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

/*
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
}*/

/*
 std::ostream& operator<<(std::ostream& os, const T& obj)
 {
 // write obj to stream
 return os;
 }
CMatrix& CMatrix::operator=(double newVal)
{
    value = newVal;
    return *this;
}*/
/*
void CMatrix::copy(CMatrix &m)
{
	int tmp_i;
	double *tmp_p;
    
	// swap all the member variables
    
	tmp_i = m_nCol; m_nCol = m.m_nCol; //m.m_nCol = tmp_i;
    
	tmp_i = m_nRow; m_nRow = m.m_nRow; //m.m_nRow = tmp_i;
    
	tmp_p = m_aData; m_aData = m.m_aData; //m.m_aData = tmp_p;
 
 You want to output the string contained into your MyString object, so you should replace
 
 os << data;
 with
 
 os << data.text;
 This is the whole point of having a friend function.
 
 As it is, you do an infinite recursion
 because os << data; calls itself the << operator of your function
 (data is of type MyString)
}*/

//http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
/*
dumb_array& operator=(dumb_array other) // (1)
{
    swap(*this, other); // (2)

    return *this;
} 
 Why does it work?
 
 We first notice an important choice:
 the parameter argument is taken by-value.
 While one could just as easily do the following
 (and indeed, many naive implementations of the idiom do):
 
 dumb_array& operator=(const dumb_array& other)
 {
 dumb_array temp(other);
 swap(*this, temp);
 
 return *this;
 }

 We lose an important optimization opportunity. 
 Not only that, but this choice is critical in C++11, 
 which is discussed later. 
 (On a general note, a remarkably useful guideline is as follows: 
 if you're going to make a copy of something in a function, 
 let the compiler do it in the parameter list.‡)

 //for operator= taking its argument per copy.
 */


//CMatrix& CMatrix::operator=(CMatrix& newCVar) { swap(newCVar); std::cout << "went in fx with amp in param"; return *this; }

// http://stackoverflow.com/questions/4421706/operator-overloading
CMatrix& CMatrix::operator=(CMatrix& otherMatrix) //CMatrix& otherMatrix // tried without amp too
{
	CMatrix m(otherMatrix.getNRow(), otherMatrix.getNCol());

//	for (int i = 0; (i < getNRow()) && (i < m.getNRow()); ++i)
//		for (int j = 0; (j < getNCol()) && (j < m.getNCol()); ++j)
//			m.element(i, j)  = element(i, j);

	// We don't need assignment here because we don't need m any more!
	swap(m);

	return *this;

	// m's destructor will be called here.
	// The old m_aData will be deleted then.



/////	std::cout << "went in this fx with no amp in param";
    /*
    int tmp_i;
	double *tmp_p;
    
	// swap all the member variables
    
	tmp_i = m_nCol; m_nCol = m.m_nCol; m.m_nCol = tmp_i;
	tmp_i = m_nRow; m_nRow = m.m_nRow; m.m_nRow = tmp_i;
	tmp_p = m_aData; m_aData = m.m_aData; m.m_aData = tmp_p;
     */
    //int		m_nRow; // # of rows
	//int		m_nCol; // # of columns
    // double	*m_aData;
    //value = otherMatrix.value;
    //m_aData = otherMatrix.m_aData;
    //return *this;
    
    //this->m_nCol = otherMatrix.m_nCol;
    //this->m_nRow = otherMatrix.m_nRow;
    //this->m_aData = otherMatrix.m_aData;
    //swap(otherMatrix);
    
    ////CMatrix temp(otherMatrix.getNRow(), otherMatrix.getNCol());
    ////temp.swap(otherMatrix);
    
    //this->swap(temp);
    //swap(temp);
 /////   m_nRow = otherMatrix.getNRow();
 /////   m_nCol = otherMatrix.getNCol();
    //this->
  /////  swap(otherMatrix);

    //swap(CMatrix temp(otherMatrix.getNRow(), otherMatrix.getNCol()));
    
   ///// return *this;
}

/*
 You want to output the string contained into your MyString object,
 so you should replace
 os << data;
 with
 os << data.text;
 This is the whole point of having a friend function.
 As it is, you do an infinite recursion because os << data;
 calls itself the << operator of your function (data is of type MyString)
 */
/*
 Operators for Pointer-like Types
 
 For defining your own iterators or smart pointers,
 you have to overload the unary prefix dereference operator *
 and the binary infix pointer member access operator ->:
 
 class my_ptr {
 value_type& operator*();
 const value_type& operator*() const;
 value_type* operator->();
 const value_type* operator->() const;
 };
 Note that these, too, will almost always need both a const and a non-const version. For the -> operator value_type must be of class (or struct or union) type, otherwise their implementation results in a compile-time error.
 */

//Also note that operator+ takes its left operand by copy
//rather than by const reference.
//The reason for this is the same as the reason giving
//for operator= taking its argument per copy.

//double& CVariable::operator*() { return value; }
//double CVariable::operator*() const { return value; }
//double& CVariable::operator=(double newValue) { value = newValue; return value; }
//double& CVariable::operator=(double& newValue) { value = newValue; return value; }
//CVariable& CVariable::operator=(CVariable& newCVar) { value = newCVar.value; return *this; }

/*Assignment, at its heart, is two steps: tearing down the object's old state and building its new state as a copy of some other object's state.

Basically, that's what the destructor and the copy constructor do, so the first idea would be to delegate the work to them. However, since destruction mustn't fail, while construction might, we actually want to do it the other way around: first perform the constructive part and if that succeeded, then do the destructive part. The copy-and-swap idiom is a way to do just that: It first calls a class' copy constructor to create a temporary, then swaps its data with the temporary's, and then lets the temporary's destructor destroy the old state.
Since swap() is supposed to never fail, the only part which might fail is the copy-construction. That is performed first, and if it fails, nothing will be changed in the targeted object.

In its refined form, copy-and-swap is implemented by having the copy performed by initializing the (non-reference) parameter of the assignment operator:

T& operator=(T tmp)
{
    this->swap(tmp);
    return *this;
}
*/


CMatrix& CMatrix::operator+(CMatrix& other)
{
	// check that both are same size
	// if they are not return null don't try to add or subtract
    
	// assuming both alreaady same size...
	CMatrix sum(m_nRow, m_nCol); // solution matrix
    
	// use same method as swap or resize or whatever
	// to access same row,col cell on each matrix at same time
	for (int i = 0; (i < getNRow()) && (i < other.getNRow()); ++i)
		for (int j = 0; (j < getNCol()) && (j < other.getNCol()); ++j)
			sum.element(i, j) = element(i, j) + other.element(i, j);
    
    /*
    CMatrix-soln.cpp:266:9:
    warning: reference to stack memory associated with local
    variable 'sum' returned [-Wreturn-stack-address]*/
	return sum;
}

