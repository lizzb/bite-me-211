#include "CMatrix-soln.h"

#include <iostream>
#include <string>
using namespace std;

//ostream& operator<<(std::ostream& out, CMatrix& cdb);
ostream& operator<<(std::ostream& out, CMatrix& m);

int main()
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
        m3("[1.1 1.1 0; 1.1 0 1.1]"), // for adding
		mstr("[1.2 3.4 5.6; 2.1 4.3 6.5]"), // matrix from string
		merr("[1.2 3.4 5.6; 2.1]"); // bad input


	cout << "A null matrix:" << endl;
	//printMatrix(null);
    cout << null;

	cout << "m1 An 1 by 1 matrix:" << endl;
	printMatrix(m1);
    cout << m1;

	cout << "m2 A 2 by 2 matrix:" << endl;
    cout << m2;
	//printMatrix(m2);
    /*
    m1 = m2;
    cout <<" after setting m1 to m2" << endl;
    cout <<" m1" << endl;
    printMatrix(m1);
*/
	cout << "A 2 by 3 matrix:" << endl;
	cout << mstr; //printMatrix(mstr);
    
    cout << "Add another 2 by 3 matrix:" << endl;
    cout << "other" << endl;
    cout << m3;
    cout << "sum" << endl;
    CMatrix sum = m3 + mstr;
    //cout << sum; // malloc
    cout << m3 + mstr; // seg fault
    //CMatrix twobyThree(m3);//twobythree(2, 3);
    //cout << twobythree; //printMatrix(mstr);
    //twobythree = mstr + m3;
	//cout << twobythree; //printMatrix(mstr);
    
   /* m1 = mstr;
    cout <<" after setting m1 to mstr" << endl;
    cout <<" m1" << endl;
    printMatrix(m1);
*/
	cout << "A invalid matrix:" << endl;
	cout << merr; //printMatrix(merr);

	cout << "Resize to 3 by 4:" << endl;
	mstr.resize(3, 4); // resize to 4 by 3
	cout << mstr; //printMatrix(mstr);

	cout << "Resize to 2 by 2:" << endl;
	mstr.resize(2, 2); // resize to 2 by 2
	cout << mstr; //printMatrix(mstr);

	//cout << "Press any key to end...";
	//cin.get();	// wait for a key to end your program
    return 0;
}


//CMatrix& CMatrix::operator<<(CMatrix& otherMatrix)
ostream& operator<<(std::ostream& out, CMatrix& m)
{
    
    if (m.IsNull()) out << "\tnull matrix" << endl;
		//std::cout << "\tnull matrix" << std::endl;
	else
	{
		// row by row
		for (int i = 0; i < m.getNRow(); ++i)
		{
			//std::cout << "\t";
            out << "\t";
			for (int j = 0; j < m.getNCol(); ++j) out << m.element(i, j) << "\t";
				//std::cout << m.element(i, j) << "\t";
			//std::cout << std::endl;
            out << endl;
		}
	}
    out << endl;
	//std::cout << std::endl;
    return out;
    
    /*cout << "Variables: \n";
     int len = cdb.db.size();
     for (int i = 0; i < len; i++)
     out << cdb.db[i] << endl;
     return out;
     */
    //printMatrix(m);
}

//double& CVariable::operator*() { return value; }
//double CVariable::operator*() const { return value; }