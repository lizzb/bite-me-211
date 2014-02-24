//
// main.cpp
//

#include "cvariable.h"

// true for an error and false for okay makes NO SENSE
// also in c++ strings are better than char*... prof must be used to C programming

// performs a simple assignment statement, like "x = 1";
// returns true if there is some error in the assignment and false otherwise
bool assign(const char* lhs, const char* rhs)
{
    // returns true if there is some error in the assignment
    // return false otherwise
    return false;
}


// performs a unary operator statement, like "x++";
// returns true if there is some error during the operation and false otherwise
bool unary_op(const char* variable, OP unary_op)
{
    // returns true if there is some error during the operation
    // return false otherwise
    return false;
}


// performs a binary operator assignment, such as " d = 6.28 * r";
// returns true if there is some error during the operation and false otherwise
bool binary_op(const char* left, OP operator, const char* right)
{
    // returns true if there is some error during the operation
    // return false otherwise
    return false;
}


// performs a binary operator assignment, such as " d = 6.28 * r";
// returns true if there is some error during the operation and false otherwise
bool binary_assign(const char* assign_var, const char* left, OP operator, const char* right)
{
    // returns true if there is some error during the operation
    // return false otherwise --> this makes no sense
    return false;
}


// evaluates a numeric string or variable name to its numeric value;
//returns true if expression is an invalid number or variable does not exist
bool get_value(const char* expression, double& value)
{
    //returns true if expression is an invalid number or variable does not exist
    // return false otherwise???? --> assumed,
    // but again, decision of true v false makes no sense
    return false;
}


// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar)
{
    
}
// prints out every CVariable in the DB
ostream& operator<<(ostream& out, CVarDB& cdb)
{
    
}

// dont forget your main function.....

int main()
{
    // print welcome message
    cout << endl;
    cout << "\tWelcome to the EECS 211 MP#3: A Command Line Interpreter" << endl;
    cout << "\t\tNan Jiang, Northwestern University "<< endl;
    cout << "\t\t   Copyright, 2014   " << endl;   

    //Get the input
    string Buffer;

    int num_Case=0;

    ifstream TestFile("testcase.txt"); // read from file

    if (TestFile.is_open())// open file
    {
        while ( getline(TestFile,Buffer) )// read a command line
        {
            if (Buffer.compare("quit")==0) // if the input is 'quit'
            {
                cout<<"\nThank you. "; //quit the program
                break;
            } 
            else
            {
                // process the command line
                cout<<"\n# "<<++num_Case <<" : "<<Buffer<<endl; // print the command line
                Interpreter(Buffer);
            }
        }
        TestFile.close();
    }

    else 
    {
        cout << "Unable to open file"; 
    }


    cout<<"Press any key to exit..."<<endl;
    getchar();        


}



