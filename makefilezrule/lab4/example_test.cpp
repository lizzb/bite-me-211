#include "CMatrix-soln.h"

#include <iostream>
#include <string>
using namespace std;

//ostream& operator<<(std::ostream& out, CMatrix& cdb);
ostream& operator<<(std::ostream& out, CMatrix& m);

int main()
{
	// print welcome message
	//cout << endl << "\tWelcome to the EECS 211 MP#4: CMatrix Classes" << endl;
	//cout << "\t\tYour Name, Northwestern University "<< endl;
	//cout << "\t\t   Copyright, 2014   " << endl;   
	cout << "\t\t   CMatrix Tests  " << endl;   

	CMatrix null;		// null matrix
	CMatrix m1(1.1);	// 1 by 1 matrix with element 1.1
	CMatrix m2(2, 2);	// 2 by 2 matrix filled with 0's

	CMatrix merr("[1.2 3.4 5.6; 2.1]"); 		// bad input
	CMatrix mstr("[1.2 3.4 5.6; 2.1 4.3 6.5]"); // matrix from string
	CMatrix m3("[1.1 1.1 0; 1.1 0 1.1]");		// for adding
	//CMatrix twobyThree(2, 3);

	/*
	cout << "A null matrix:" << endl;
	cout << null;

	cout << "m1:   An 1 by 1 matrix:" << endl;
	cout << m1;

	cout << "m2:   A 2 by 2 matrix:" << endl;
	cout << m2;
	*/
	/*
    cout << "A 2 by 3 matrix:" << endl;
	cout << mstr;

	
	cout << "A invalid matrix:" << endl;
	cout << merr;

	cout << "Resize to 3 by 4:" << endl;
	mstr.resize(3, 4); // resize to 4 by 3
	cout << mstr;

	cout << "Resize to 2 by 2:" << endl;
	mstr.resize(2, 2); // resize to 2 by 2
	cout << mstr;
	*/
	/*
	// Equals override
    m1 = m2;
    cout <<" after setting m1 to m2  " << endl;
    cout <<"m1  " << endl;
	
	m1 = mstr;
    cout <<"after setting m1 to mstr  " << endl;
    cout <<"m1 " << endl;
	*/

	cout << "Add the following 2 by 3 matrices:" << endl;

	cout << "mstr: " << endl << mstr;
	cout << "other matrix" << endl << m3;

	cout << "sum of matrices" << endl;
	
	CMatrix sum = m3 + mstr;
    cout << sum; 		// malloc - but gives sum
    //cout << m3 + mstr;	// seg fault - no sum

	//cout << "Press any key to end...";
	//cin.get();	// wait for a key to end your program
	return 0;
}

// Print out the matrix to the command line
//CMatrix& CMatrix::operator<<(CMatrix& otherMatrix)
ostream& operator<<(std::ostream& out, CMatrix& m)
{
	if (m.IsNull()) out << "\tnull matrix" << endl;
	else
	{
		// row by row
		for (int i = 0; i < m.getNRow(); ++i)
		{
			out << "\t";
			for (int j = 0; j < m.getNCol(); ++j)
				out << m.element(i, j) << "\t";
				// would be nice to override this with [][]
			out << endl;
		}
	}
	out << endl;
	return out;
 }
