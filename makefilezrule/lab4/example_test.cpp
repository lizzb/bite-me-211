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

	cout << "m1: " << endl << m1;
	CMatrix m1x2(2.2);
	cout << "m1x2: " << endl << m1x2;
	cout << "m1 == m1x2 " << (m1 == m1x2) << endl;
	cout << "m1 != m1x2 " << (m1 != m1x2) << endl;
	cout << "m1 x matrix containing 1 element, 2.0 " << endl;
	CMatrix dub(2.0);
	//cout << m1 * dub; //segfault
	CMatrix dubxm1 = m1 * dub; // malloc issues later

	cout << "dubxm1: " << dubxm1;
	cout << "dubxm1 == m1x2 " << (dubxm1 == m1x2) << endl;
	cout << "dubxm1 != m1x2 " << (dubxm1 != m1x2) << endl;


    cout << "m1: " << endl << m1;
    cout << "mstr: " << endl << mstr;
    cout << "other matrix m3" << endl << m3;

	cout << "multiply: mstr x m1 (scalar value) " << endl;
    CMatrix prod = m1 * mstr;
    cout << prod;

    cout << "multiply: (scalar value) m1 x mstr " << endl;
    CMatrix prod2 = m1 * mstr;
    cout << prod2;

	cout << "divide: mstr / m1 (scalar value) " << endl;
    CMatrix quotient = mstr / m1;
    cout << prod;

    cout << "multiply: (scalar value) m1 / mstr " << endl;
    CMatrix quotient2 = m1 / mstr;
    cout << quotient2;    


    
    cout << "Add the following 2 by 3 matrices:" << endl;
	cout << "sum of matrices m3 and mstr" << endl;

	//----
	CMatrix sum = m3 + mstr;
    cout << sum; 		// malloc - but gives sum

    //cout << m3 + mstr;	// seg fault - no sum
    //----

    cout << "mstr + m3" << endl;
    CMatrix sum2 = mstr + m3;
    cout << sum2;

    cout << "mstr - m3" << endl;
    CMatrix diff = mstr - m3;
    cout << diff;

    cout << "m3 - mstr" << endl;
    CMatrix diff2 = m3 - mstr;
    cout << diff2;
    


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
