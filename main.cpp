//
// main.cpp
//

#include "cvariable.h"

/*
#include <iostream>
#include <string>
#include <fstream>
*/
using namespace std;


// enumeration of operator types - aka "enums"
// enums allow you to refer to numbers with a more meaningful label
// for better code readability
enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC};

// function declarations
void Interpreter(string&);

// if the command line is valid unary operation
bool IsAUnary(char*, int [][2], char*, OP&);

// if it is a valid assignment
bool IsAAsn(char*, int [][2], char*, char*);

// if it is a valid binary operation
bool IsABinary3(char*, int [][2], char*, char*, OP&);

// if it is a valid assignment and binary operation
bool IsABinary5(char*, int [][2], char*, char*, char*, OP&);

// output the operator
void OpTranslator(OP);


// functions from the previous project
int Partitioner(char*, int [][2], int&); // partitioning the command line into segments
bool IsAChar(char); // if input is a letter
bool IsADigit(char); // if it is a digit
bool IsAOperator(char); // if it is an operator


int main()
{
    // print welcome message
    cout << endl;
    cout << "\tWelcome to the EECS 211 MP#3: A Command Line Interpreter" << endl;
    cout << "\t\tNan Jiang, Northwestern University "<< endl;
    cout << "\t\t   Copyright, 2014   " << endl;   

    // This will store the input
    string Buffer;

    int num_Case=0;
    
    /*
     res = var_1 + 3.1415
     M_1 = [1 2 3; 3 4 5; 4 3 2]
     a++
     c = d
     a_123 = 123
     ++m
     a + b
     a = b +c -d *9
     a +=9
     var_r = var_1 + 3.1415
     This MP is 4 fun
     a ++
     M_1 - 123
     quit
     */
    
    // read from file
    ifstream TestFile("testcase.txt");

    // Open file (assumes file is valid if able to be opened?)
    if (TestFile.is_open())
    {
        // read a command line
        while ( getline(TestFile,Buffer) )
        {
            // if the input is 'quit'
            if (Buffer.compare("quit")==0) 
            {
                // quit the program   
                cout << "\nThank you. ";
                break; 
            } 
            else
            {
                // print the command line
                cout<<"\n# "<< ++num_Case <<" : "<<Buffer<<endl;

                // process the command line
                Interpreter(Buffer);
            }
        }

        // quit the program
        TestFile.close();
    }

    else 
    {
        cout << "Unable to open file"; 
    }


    cout << "Press any key to exit..." << endl;
    getchar();        

}
/*
Input the command line here:a = 5

Input the command line here:who

ans 0
a  	5

Input the command line here:b = a+5
b = 10

Input the command line here:who

ans 0
a  	5
b  10


Input the command line here:c = a+b
c = 15

Input the command line here:who

ans 0
a  	5
b  10
c  15

Input the command line here:tt=a*c
tt = 75

Input the command line here:who

ans     0
a  	5
b    10
c    15
tt    75

Input the command line here:
*/


// if input is a letter
bool IsAChar(char str) { return ((str>='A'&&str<='Z')||(str>='a'&&str<='z')); }

// if input is a digit
bool IsADigit(char str) { return ((str>='0'&&str<='9')||(str=='.')); }

// if input is an operator
bool IsAOperator(char str)
{
    return ((str=='+')||(str=='-')||(str=='*')||(str=='/')||(str=='='));
}

private bool isEquals(string piece) {return (strcmp(piece,"=") == 0);}
private bool isAdd(string piece) {return (strcmp(piece,"+") == 0);}
private bool isMinus(string piece) {return (strcmp(piece,"-") == 0);}
private bool isMult(string piece) {return (strcmp(piece,"*") == 0);}
private bool isDivide(string piece) {return (strcmp(piece,"/") == 0);}
private bool isDivide(string piece) {return (strcmp(piece,"+") == 0);}
/*
 function determineOperator(string piece)
 {
 // array of possible operators
 // ["=", "+", "-", "*","/"]
 if(strcmp(piece,"-")==0)
 }*/



// true for an error and false for okay makes NO SENSE
// also in c++ strings are better than char*
// ... prof must be used to C programming


/*
 * Name:     assign
 * Purpose:  performs a simple assignment statement, like "x = 1";
 * Params:   lhs, rhs
 * Returns:  true if there is some error in the assignment, false otherwise
 */
bool assign(const char* lhs, const char* rhs)
{
    // returns true if there is some error in the assignment
    // return false otherwise
    return false;
}


/* ----------------------------------------------------------------------------
 Name:     unary_op
 Purpose:  performs a unary operator statement, like "x++";
 Params:   variable, unary_op
 Returns:  true if there is some error during the operation,
           false otherwise
---------------------------------------------------------------------------- */
bool unary_op(const char* variable, OP unary_op)
{
    // returns true if there is some error during the operation
    // return false otherwise
    return false;
}


/* ----------------------------------------------------------------------------
 Name:     binary_op
 Purpose:  performs a binary operator assignment, like "d = 6.28 * r";
 Params:   left, operator, right
 Returns:  true if there is some error during the operation, false otherwise
---------------------------------------------------------------------------- */
bool binary_op(const char* left, OP operator, const char* right)
{
    // returns true if there is some error during the operation
    // return false otherwise
    return false;
}


/* ----------------------------------------------------------------------------
 Name:     binary_assign
 Purpose:  performs a binary operator assignment, e.g. "d = 6.28 * r";
 Params:   assign_var, left, operator, right
 Returns:  true if there is an error during the operation, false otherwise
---------------------------------------------------------------------------- */
bool binary_assign(const char* assign_var, const char* left, OP operator, const char* right)
{
    // returns true if there is some error during the operation
    // return false otherwise --> this makes no sense
    return false;
}


/* ----------------------------------------------------------------------------
 Name:     get_value
 Purpose:  evaluates a numeric string or variable name to its numeric value
 Params:   expression, value
 Returns:  true if there is an error during the operation, 
           e.g. expression is an invalid number or variable does not exist
           false otherwise
---------------------------------------------------------------------------- */
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


/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
---------------------------------------------------------------------------- */

////////////////////////////////////////////////////////////////////////////////
// functions related to the command line interpreter

// We only allow:
// type asn:   e.g., a = b              (iSeg = 3)
// type unary: e.g., a++                (iSeg = 2)
// type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)


void Interpreter(string& Input)
{
    char Buffer[500]; // array buffer to hold the command line
    strncpy(Buffer, Input.c_str(), sizeof(Buffer));
    Buffer[sizeof(Buffer) - 1] = 0;

    int segmt[10][2];   // record the location of each segment

    int iSeg = 0;       // number of segments in command line

    bool Tag = false;   // why is this called Tag?!?

    OP  op; // the operator in the command line

    // result_name, operand_1 and operand_2
    char res[50], operand_1[50], operand_2[50]; 

    // if the command line can be successfully segment(ed?)
    if(Partitioner(Buffer,segmt,iSeg))
    {

        switch (iSeg) // valid cases can be : 2, 3 or 5
        {
        case 2: // the command line is possible to be unary operation
            {
                // if it is a valid unary operation
                Tag = IsAUnary(Buffer,segmt,operand_1,op); 
                if(Tag)
                {   // it is a valid unary operation, output the result
                    OpTranslator(op); 
                    cout << " " << operand_1 << endl;
                }  
                break;      
            }
        case 3: // the command line is possible to be binary operation or assignment
            {
                // if it is a valid assignment
                if(IsAAsn(Buffer,segmt,res,operand_1)) 
                {   // it is a valid assignment, output the result
                    Tag = true;
                    cout << "ASN " << " " << operand_1<< " to " << res << endl;
                }

                // if it is a binary operation with assignment to default variable ans
                else if(IsABinary3(Buffer,segmt,operand_1,operand_2,op)) 
                {   // it is a binary operation, output the result
                    Tag = true;
                    OpTranslator(op);
                    cout << " " << operand_1<<" AND "<< operand_2 << " , THEN ASN to ans. "<<endl;
                }
                break;
            }

        // the input command line is a binary operation and assignment
        case 5: // the command line is possible to be binary operation and assignment
            {
                // if it is a binary operation with assignment to a specified variable
                Tag = IsABinary5(Buffer,segmt,res,operand_1,operand_2,op); 

                if(Tag)
                {   // it is a binary operation, so output the result
                    OpTranslator(op);
                    cout<<" "<<operand_1<<" AND "<<operand_2<<" , THEN ASN to "<< res <<endl;
                }  
                break;              
            }
        }
    }



    if (Tag == false) // if the command line is not valid
    {
        cout<<"Sorry, do not understand." <<endl;
    }

}

/* ----------------------------------------------------------------------------
 Name:     IsAUnary
 Purpose:  called if the input command line is a valid unary operation
 Params:   char* Buffer   - the input command line (known)
           int segmt[][2] - location of each segment inthe command line (known)
           char* operand  - the operand in the command line (to fill in)
           OP& op         - the operator (to fill in)
 Returns:  true / 1   - valid unary operation,
           false / 0  - not a valid unary operation
---------------------------------------------------------------------------- */
bool IsAUnary(char* Buffer, int segmt[][2], char* operand, OP& op)
{
    bool isValid = false;   // rename Tag to isValid
    char piece[2][50];      // what is this?

    for (int i = 0 ; i<2; i++)
    {
        for(int j = 0; j<segmt[i][1]; j++)
        {
            piece[i][j] = Buffer[j+segmt[i][0]];
        }
        piece[i][segmt[i][1]] = '\0';
    }

    // assuming these are the operator characters but not sure
    string p0 = piece[0]; 
    string p1 = piece[1];

    if( (strcmp(p0, "++") == 0) ||  (strcmp(p0, "--") == 0)) )
    {
        if(strcmp(p0, "++") == 0) op = PRE_INC;
        else op = PRE_DEC;

        strcpy(operand, piece[1]);
        isValid = true;
    }
    /*if(strcmp(piece[0],"++")==0)
    {
        op = PRE_INC;
        strcpy(operand, piece[1]);
        isValid = true;
    }
    else if (strcmp(piece[0],"--")==0)
    {
        op = PRE_DEC;
        strcpy(operand, piece[1]);
        isValid = true;
    }
    */

    else if( (strcmp(p1, "++") == 0) ||  (strcmp(p1, "--") == 0)) )
    {
        if(strcmp(p1, "++") == 0) op = POST_INC;
        else op = POST_DEC;

        strcpy(operand, piece[0]);
        isValid = true;
    }

    /*
    else if(strcmp(piece[1],"++")==0)
    {
        op = POST_INC;
        strcpy(operand, piece[0]);
        isValid = true;
    }
    else if (strcmp(piece[1],"--")==0)
    {
        op = POST_DEC;
        strcpy(operand, piece[0]);
        isValid = true;
    }*/

    return isValid;
}

//
// Input:
// char* Buffer   : the input command line (known)
// int segmt[][2] : the location of each segment in the command line (known)
// char* res      : the reseult_name in the command line (to fill in)
// char* operand  : the operand in the command line (to fill in)
// Output:
// boolean variable : 0 -- not a valid assignment, 1 -- valid assignment

/* ----------------------------------------------------------------------------
 Name:     IsAAsn
 Purpose:  called if the input command line is a valid assignment
 Params:   char* Buffer   - the input command line (known)
 int segmt[][2] - location of each segment inthe command line (known)
 char* operand  - the operand in the command line (to fill in)
 OP& op         - the operator (to fill in)
 Returns:  true / 1   - valid unary operation,
 false / 0  - not a valid unary operation
 ---------------------------------------------------------------------------- */
bool IsAAsn(char* Buffer, int segmt[][2], char* res, char* operand)
{
    //bool Tag = false;
    char piece[3][50];
    for (int i = 0 ; i<3; i++)
    {
        for(int j = 0; j<segmt[i][1]; j++)
        {
            piece[i][j] = Buffer[j+segmt[i][0]];
        }
        piece[i][segmt[i][1]] = '\0';
    }
    if(strcmp(piece[1],"=")==0) // if the #2 piece is "="
    {
        strcpy(res, piece[0]);
        strcpy(operand, piece[2]);
        return true; //Tag = true;
    }

    // if we got here, it wasn't a valid assignment
    return false; //Tag;
}

/* ----------------------------------------------------------------------------
 Name:     IsABinary3
 Purpose:  If the input command line is a binary operation
 Params:   char* Buffer   - the input command line (known)
           int segmt[][2] - location of each segment inthe command line (known)
           char* operand  - the operand in the command line (to fill in)
           char* operand_1- the operand_1 in the command line (to fill in)
           char* operand_2- the operand_2 in the command line (to fill in)
           OP& op         - the operator (to fill in)
 Returns:  1 -- valid binary operation (true)
           0 -- not a valid binary operation (false)
---------------------------------------------------------------------------- */
bool IsABinary3(char* Buffer, int segmt[][2], char* operand_1, char* operand_2, OP& op)
{
    bool isValid = false; // Tag = false;

    char piece[3][50];
    for (int i = 0 ; i<3; i++)
    {
        for(int j = 0; j<segmt[i][1]; j++)
        {
            piece[i][j] = Buffer[j+segmt[i][0]];
        }
        piece[i][segmt[i][1]] = '\0';
    }

    // if the #2 piece is an operator
    if(strcmp(piece[1],"+")==0) 
    {
        op = ADD;
        isValid = true; //Tag = true;
    }
    else if(strcmp(piece[1],"-")==0)
    {
        op = MIN;
        isValid = true; //Tag = true;
    }
    else if(strcmp(piece[1],"*")==0)
    {
        op = MUL;
        isValid = true; //Tag = true;
    }
    else if(strcmp(piece[1],"/")==0)
    {
        op = DIV;
        isValid = true; //Tag = true;
    }
    if (isValid) //(Tag)
    {
        strcpy(operand_1, piece[0]);
        strcpy(operand_2, piece[2]);
    }

    // if we got here, it wasn't a valid assignment
    return isValid; // Tag;
}

// If the input command line is a binary operation and assignment
// Input:
// char* Buffer   : the input command line (known)
// int segmt[][2] : the location of each segment in the command line (known)
// char* res      : the reseult_name in the command line (to fill in)
// char* operand_1: the operand_1 in the command line (to fill in)
// char* operand_2: the operand_2 in the command line (to fill in)
// OP& op         : the operator (to fill in)
// Output:
// boolean variable : 0 -- not a valid binary operation and assignment, 1 -- valid binary operation and assignment

bool IsABinary5(char* Buffer, int segmt[][2], char* res , char* operand_1, char* operand_2, OP& op)
{
    bool isValid = false; // Tag = false;bool Tag = false;
    char piece[5][50];
    for (int i = 0 ; i<5; i++)
    {
        for(int j = 0; j<segmt[i][1]; j++)
        {
            piece[i][j] = Buffer[j+segmt[i][0]];
        }
        piece[i][segmt[i][1]] = '\0';
    }
    
    
    // if the #2 piece is "="
    if(isEquals(piece[1]))                  // (strcmp(piece[1],"=")==0)
    {
        // if the #4 piece is an operator 
        if(isAdd(piece[3]))                 // (strcmp(piece[3],"+")==0)
        {
            op = ADD;
            isValid = true; //Tag = true;
        }
        else if(isMinus(piece[3]))            // (strcmp(piece[3],"-")==0)
        {
            op = MIN;
            isValid = true; //Tag = true;
        }
        else if(isMult(piece[3]))             // (strcmp(piece[3],"*")==0)
        {
            op = MUL;
            isValid = true; //Tag = true;
        }
        else if(isDivide(piece[3]))         // (strcmp(piece[3],"/")==0)
        {
            op = DIV;
            isValid = true; //Tag = true;
        }
        if (isValid) //(Tag)
        {
            strcpy(res, piece[0]);
            strcpy(operand_1, piece[2]);
            strcpy(operand_2, piece[4]);
        }
    }

    return isValid; //Tag;
}

// explain operators (??)
void OpTranslator(OP op) 
{
    /*if(op == ASN || op == ADD || op == MIN || op == MUL || op == DIV ||
       op == PRE_INC || op == PRE_DEC || op == POST_INC || op == POST_DEC)
    {
        cout << op.toString();
        
    }*/
    switch(op)
    {
    case ASN:
        cout << "ASN" ; break;
    case ADD:
        cout << "ADD" ; break;
    case MIN:
        cout << "MIN" ; break;
    case MUL:
        cout << "MUL" ; break;
    case DIV:
        cout << "DIV" ; break;
    case PRE_INC:
        cout << "PRE_INC" ;
        break;
    case PRE_DEC:
        cout << "PRE_DEC" ;
        break;
    case POST_INC:
        cout << "POST_INC" ;
        break;
    case POST_DEC:
        cout << "POST_DEC" ;
        break;
    default:
        cout << "UNRECOGNIZED OPERATOR" ;
        break;
    }
}



////////////////////////////////////////////////////////////////////////////////
// functions from MP#2

int Partitioner(char* Buffer,  int segmt[][2], int& iSeg)
{
    // indicator
    int st=0;
    int ed=0;
    int error_code = 1;

    int len = (int)strlen(Buffer)-1;


    while(st<len)
    {
        while(Buffer[st]==' '&&st<len)st++;

        ed = st;

        if(st==len)
        {
            if (iSeg==0) { error_code = 0; }
            break;
        }
        else
        {
            if(IsAChar(Buffer[st]))
            {
                while((ed<len)&&(IsAChar(Buffer[ed])||IsADigit(Buffer[ed])||Buffer[ed]=='_'))ed++;
            }
            else if(IsADigit(Buffer[st]))
            {
                while((ed<len)&&(IsADigit(Buffer[ed])||Buffer[ed]=='.'))ed++;
            }
            else if(IsAOperator(Buffer[st]))
            {
                while((ed<len)&&(IsAOperator(Buffer[ed])))ed++;
            }
            else if(Buffer[st]=='[')
            {
                ed = st+1;
                while((ed<len)&&(Buffer[ed]!=']'))
                {
                    if(IsADigit(Buffer[ed])||(Buffer[ed]==',')||(Buffer[ed]==';')||(Buffer[ed]==' ')||(Buffer[ed]=='.'))
                    {
                        ed++;
                    }
                    else
                    {
                        cout << "Expect a ']' here." << endl;
                        error_code = 0;
                        break;
                    }
                    ed++;
                }
            }
            else if(Buffer[st]==';')ed++;
            else { error_code = 0; }

        }
        if(error_code)
        {
            segmt[iSeg][0] = st;
            segmt[iSeg][1] = ed-st;
            iSeg = iSeg + 1;
            st = ed;
        }  
        else { break; }
    } 

    return error_code;
}



