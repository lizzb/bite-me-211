#include "CMatrix.h"

#include <iostream>
#include <string>
using namespace std;

void main()
{
	// print welcome message
	cout << endl;
	cout << "\tWelcome to the EECS 211 MP#4: CMatrix Classes" << endl;
	cout << "\t\tYour Name, Northwestern University "<< endl;
	cout << "\t\t   Copyright, 2014   " << endl;   

	CMatrix
		null, // null one
		m1(1.1), // 1 by 1 matrix with element 1.1
		m2(2, 2), // 2 by 2 zero matrix
		mstr("[1.2 3.4 5.6; 2.1 4.3 6.5]"), // matrix from string
		merr("[1.2 3.4 5.6; 2.1]"); // bad input


	cout << "A null matrix:" << endl;
	printMatrix(null);

	cout << "An 1 by 1 matrix:" << endl;
	printMatrix(m1);

	cout << "A 2 by 2 matrix:" << endl;
	pintMatrix(m2);

	cout << "A 2 by 3 matrix:" << endl;
	printMatrix(mstr);

	cout << "A invalid matrix:" << endl;
	printMatrix(merr);

	cout << "Resize to 3 by 4:" << endl;
	mstr.resize(3, 4); // resize to 4 by 3
	printMatrix(mstr);

	cout << "Resize to 2 by 2:" << endl;
	mstr.resize(2, 2); // resize to 2 by 2
	printMatrix(mstr);

	cout << "Press any key to end...";
	cin.get();	// wait for a key to end your program
}