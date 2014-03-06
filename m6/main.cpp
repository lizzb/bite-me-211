/* ----------------------------------------------------------------------------

main.cpp 

the parser and interpreter that run your MiniMatlab program.

Starting from your Lab 4 and Lab 5 solutions
(or the provided code and sample solution), 
your MiniMatlab should be able to
construct and manipulate matrix values and variables
---

cvariable.cpp + cvariable.h
Define the classes used to store and manipulate variables

cmatrix.cpp + cmatrix.h   - Define the CMatrix class





Based off Lab 5 Sample Solution

wow i love how thorough the commenting is so that the professor can clear up
any misconceptions or common mistakes the students had... -_-

... i'm also loving all of the SUPER subtle changes to names that could have
students wondering why nothing will compile...




// main function
// read input test cases from "TestCases.txt"
// see expected output in "Output.jpg"

// Your submission should read test cases from the file "TestCase.txt".


// Update the code in the interpreter function
// (including any helper fx's like binary_assign_op and getValue)
// to operate in terms of CMatrices
// rather than double values !!


// Invalid matrix operations should result in an error message
// such as "Sorry, do not understand" or
// "Invalid operation, matrix size does not match."

// Example invalid matrix operations:
// (be sure to test each of these in your main function!)

// Adding together matrices of different sizes

// Dividing by a matrix (not scalar) value

---------------------------------------------------------------------------- */

/**
 Lab 5:  a Programmable Calculator (Sample Solution)

 This program can add, subtract, multiply, and divide numbers, as well as store
 and retrieve variable values.  It accepts a sequence of commands from the file
 "TestCase.txt" and outputs the reponses to those commands to the console.  The
 program accepts 5 basic types of commands, listed below.

 Binary operation
   Command that takes two values or variables and combines them according to
   one of the 4 basic operations (+, -, *, /).  The result is printed and 
   stored in the variable ans.
   
   Examples:  3 * 7, a + 5

 Assignment
   Command that assigns a value to a variable.  May also assign the value of
   one variable to another.  If the variable on the LHS of the assignment does
   not yet exist, it is created.  Otherwise, the existing variable is updated.
   
   If a compound assignment operator (+=, -=, *=, /=) is used in place of the
   standard assignment operator (=), the variable on the LHS is modified by the
   value on the RHS of the compound assignment (according to +, -, *, /) and
   the new value is saved.

   Examples:  myVar = 42, x = y, var_1 += 3.5

 Binary operation and assignment
   Command that performs a binary operation and assigns the result to a 
   variable.  If the variable on the LHS of the assignment does not exist, it
   is created.  Otherwise, the existing variable is updated.  Compound
   operators are not supported with this command type.


   
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string> // yeah pretty sure you don't need all this shit, esp not string AND string.h...
#include <string.h>
#include "cvariable.h"
using namespace std; 

// ewww why would you use define in this case WHYYY it should be const ugh
#define INPUT_FILE "TestCase.txt"

// lulz isn't it supposed to be ans like answer but its spelled wrong
enum op_t  {ASN, ADD, SUB, MULT, DIV, INC, DEC, ADDASN, SUBASN, MULTASN, DIVASN, BAD_OP}; // Niang
enum seg_t {VAR, NUM, MAT, OP, BAD_SEG}; // Niang

//  enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC};  // Hendrix

typedef struct
{
  char* str;
  seg_t type;
} segment_t;

/*
In order to have a single, universal database for variables,
you may wish to declare a CVarDB pointer as a global variable
and refer to this in your main.cpp file. 
*/
CVarDB* db; 

void interpreter(const char* cmd);  // Niang
//  void Interpreter(string&);      // Hendrix

op_t recognizeOp(const char* op);   // Niang

// output the operator
//void OpTranslator(OP);            // Hendrix


bool partitioner(const char* cmd, segment_t** segmt, int& numseg);

// partitioning the command line into segments
//int Partitioner(char*, int [][2], int&);           //Hendrix

void freeSegments(segment_t* segmt);

bool isChar(char c);
bool isDigit(char c);
bool isOperator(char c);
bool isSpace(char c);

//bool IsAChar(char);     // if input is a letter    // Hendrix
//bool IsADigit(char);    // if it is a digit        // Hendrix
//bool IsAOperator(char); // if it is an operator    // Hendrix


bool unary_op(const char* operand, op_t op);        // Niang

// if the command line is valid unary operation
//bool IsAUnary(char*, int [][2], char*, OP&);      // Hendrix



// Niang
bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right);

// Niang
bool binary_op(const char* left, op_t op, const char* right);

bool assign_op(const char* lhs, const char* rhs);   // Niang

bool getValue(const char* expr, double& value);     // Niang

void add(CVariable& cvar);  // Niang

 

 
 // if it is a valid assignment
 //bool IsAAsn(char*, int [][2], char*, char*);     // Hendrix

 // if it is a valid binary operation
 //bool IsABinary3(char*, int [][2], char*, char*, OP&);    // Hendrix
 
 // if it is a valid assignment and binary operation
 //bool IsABinary5(char*, int [][2], char*, char*, char*, OP&); //Hendrix

/*
  // IsABinary3 and IsABinary5 are hilarious names
 bool isEquals(char* piece); // zz
 bool isAdd(char* piece);    // lizz made
 bool isMinus(char* piece);  // lizz
 bool isMult(char* piece);   //zz
 bool isDivide(char* piece); //zz
 bool isDivide(char* piece); //zz
 bool isInc(char* piece);    //zz
 bool isDec(char* piece);    //zz
 */




/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
int main()
{
  db = new CVarDB();  

  //Get the input
  string cmd; 
  ifstream in(INPUT_FILE);   // read from file

  cout << "\tWelcome to EECS 211 Lab 5:  Programmable Calculator" << endl; 
  cout << "\tWilliam Hendrix, Northwestern University "<< endl; 
  cout << "\tCopyright 2014   " << endl;    

  if (!in.is_open())
    cout << "Unable to open input file " << INPUT_FILE << endl;   
  else
  {
    while (getline(in, cmd))
    {
      //Special commands:  quit and who
      if (cmd == "quit")
      {
        cout << "Thank you. Now closing...\n";  
        break;
      }
      else if (cmd == "who")
      {
        cout << *db;
        continue; 
      }

      //Otherwise, interpret and run the command normally
      interpreter(cmd.c_str()); 
    }

    in.close();  
  }

  delete db;  
  char c;  
  cout << "Type 'q' to quit: ";  
  cin >> c;  

  return 0;  




  /*

  You should also test to ensure that your code can still handle
  simple numeric assignments, like pi = 3.1415 without error.

  */


  /*

  test these one by one
  new matrix operations: +, -, *, /, ==, and !=

  constructs some sample matrices, 
  performs the operations, 
  and prints the results. 
  You should be sure to test that the operations work as expected 
  for both valid and invalid inputs.

  */


  /* 
  1) implement + test the new CVariable functions
      test one at a time!
  2) incorporate the improved CVariables
      modifying getValue() and
      modifying the assign_op function
        to allow your program to handle
        assignment statements involving matrices
        (e.g., mat_1 = [1 2; 3 4]). 
  3) test that basic numeric assignments still work
  4) implement + test the new matrix operations: +, -, *, /, ==, and !=
      test one at a time!
  5) incorporate the new matrix operations
      modifying the binary_assign_op fx and
      modifying the binary_op fx
        in your interpreter code


You can test these changes on the provided test file,
    as well as any cases that you used
    in testing the matrix operations in the previous step.
  ....
  N) Your submission should read test cases from the file "TestCase.txt".
  */
}


/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
bool partitioner(const char* cmd, segment_t** segmt, int& numseg)
{
  int pos, len, bpos, count;
  char* buffer;
  char c;

  //First loop:  input checking and segment counting
  pos = numseg = 0;
  len = strlen(cmd);
  while (pos < len)
  {
    c = cmd[pos];
    if (isChar(c)) //Variable
    {
      pos++;
      //Characters after the first are allowed to be 0-9
      while (pos < len && (isChar(cmd[pos]) || (cmd[pos] >= '0' && cmd[pos] <= '9'))) 
        pos++;
    }
    else if (c == '-')  //Negative number or operator
    {
      pos++;
      if (pos < len && isDigit(cmd[pos])) //Negative number
        while (pos < len && isDigit(cmd[pos]))
          pos++;
      else if (pos < len && isOperator(cmd[pos])) //Operator
        while (pos < len && isOperator(cmd[pos]))
          pos++;
    }
    else if (isOperator(c)) //Operator
    {
      pos++;
      while (pos < len && isOperator(cmd[pos]))
        pos++;
    }
    else if (isDigit(c)) //Scalar
    {
      pos++;
      while (pos < len && isDigit(cmd[pos]))
        pos++;
    }
    else if (c == '[') //Matrix
    {
      pos++;
      //We'll check matrix validity in CMatrix (Lab 6)
      //We won't worry about it here
      while (pos < len && cmd[pos] != ']')
        pos++;
      pos++; //Skip over ']'
    }
    else if (isSpace(c)) //Whitespace
    {
      pos++;
      continue; //Don't advance to next segment!
    }
    else //Unrecognized case
      return false;
    numseg++;
  }

  //Macro function to make code easier to read
#define push_to_buffer() {buffer[bpos] = cmd[pos]; pos++; bpos++;}

  //Second loop:  populating segmt structure
  *segmt = new segment_t[numseg];
  buffer = new char[len + numseg];

  bpos = pos = count = 0;
  while (pos < len)
  {
    (*segmt)[count].str = &buffer[bpos]; //Segment count starts at this position
    c = cmd[pos];
    if (isChar(c)) //Variable
    {
      (*segmt)[count].type = VAR;

      //Characters after the first are allowed to be 0-9
      while (pos < len && (isChar(cmd[pos]) || (cmd[pos] >= '0' && cmd[pos] <= '9'))) 
        push_to_buffer();
    }
    else if (c == '-')  //Negative number or operator
    {
      buffer[bpos] = '-';
      pos++;
      bpos++;
      if (pos < len && isDigit(cmd[pos])) //Negative number
      {
        (*segmt)[count].type = NUM;
        while (pos < len && isDigit(cmd[pos]))
          push_to_buffer();
      }
      else //Operator
      {
        (*segmt)[count].type = OP;
        while (pos < len && isOperator(cmd[pos]))
          push_to_buffer();
      }
    }
    else if (isOperator(c)) //Operator
    {
      (*segmt)[count].type = OP;
      while (pos < len && isOperator(cmd[pos]))
        push_to_buffer();
    }
    else if (isDigit(c)) //Scalar
    {
      (*segmt)[count].type = NUM;
      while (pos < len && isDigit(cmd[pos]))
        push_to_buffer();
    }
    else if (c == '[') //Matrix
    {
      (*segmt)[count].type = MAT;
      while (pos < len && cmd[pos] != ']')
        push_to_buffer();
      //Add ']' to buffer, as well
      push_to_buffer();
    }
    else if (isSpace(c)) //Whitespace
    {
      pos++;
      continue; //Don't advance to next segment!
    }
    else //Should never execute
    {
      delete buffer;
      delete segmt;
      return false;
    }
    
    buffer[bpos] = '\0';  //Null-terminate this segment
    bpos++;
    count++; //Advance to next segment
  }

  return true;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void freeSegments(segment_t* segmt)
{
  delete segmt[0].str;
  delete segmt;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
bool isChar(char c)
{
  if (c >= 'a' && c <= 'z')
    return true;
  else if (c >= 'A' && c <= 'Z')
    return true;
  else
    return c == '_'; //... this actually doesnt make sense
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
bool isDigit(char c)
{
  if (c >= '0' && c <= '9')
    return true;
  else
    return c == '.'; //... this actually doesnt make sense
}

/* ----------------------------------------------------------------------------
 Returns:  True if the given character is one of the valid operators
 ---------------------------------------------------------------------------- */
bool isOperator(char c)
{
  switch(c)
  {
  case '=':
  case '+':
  case '-':
  case '*':
  case '/':
    return true;
  default:
    return false;
  }
}

/* ----------------------------------------------------------------------------
 Returns:  True if the given character was a space
 ---------------------------------------------------------------------------- */
bool isSpace(char c)
{
    return( c ==' ' || c =='\t' || c =='\n' || c == '\r');
    /*
  switch(c)
  {
  case ' ':
  case '\t':
  case '\n':
  case '\r':
    return true;
  default:
    return false;
  }
     */
}

/*
You will need to update your main.cpp file from Lab 3
so that your command interpreter will be able to accomplish the following:
recognize variables, numbers, and operators
perform operations for =, +, -, *, /, ++, and --
(compound operators, like +=, -=, etc., are a bonus)
construct and manage a "system variable database" to hold all the variables
register, modify, and retrieve variable values as necessary
recognize the "who" command and print out all of the currently defined variables in response
report the results or appropriate error messages to the user
recognize the "quit" command to end the program
*/

/* Ten points extra credit will be awarded if your solution
is able to handle (non-scalar) matrix multiplication as well.
For example, if the variables a and b are defined by
a = [1 2; 3 4] and b = [5 9; 3 1], a * b should yield 
the output [11 11; 27 31 (not [5 18; 9 4]).
*/
/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void interpreter(const char* cmd)
{
	char buffer[500];
	segment_t* segmt;
	char* lhs;
  char* left;
  char* right;
  op_t op;
  int numSeg;
  bool success;

  if (partitioner(cmd, &segmt, numSeg))
	{
#ifdef DEBUG
    for (int i = 0; i < numSeg; i++)
    {
      if (segmt[i].type == VAR)
        cout << "Variable:  " << segmt[i].str << endl;
      else if (segmt[i].type == NUM)
        cout << "Scalar:    " << segmt[i].str << endl;
      else if (segmt[i].type == OP)
        cout << "Operator:  " << segmt[i].str << endl;
      else if (segmt[i].type == MAT)
        cout << "Matrix:    " << segmt[i].str << endl;
      else
        cout << "Error in parsing\n";
    }
#endif

    success = true;
    cout << cmd << endl;
		switch (numSeg) //Must have 2, 3, or 5 segments
		{
		case 2: //Unary operation
      if (segmt[0].type == OP && segmt[1].type == VAR)
      {
        left = segmt[1].str;
        op = recognizeOp(segmt[0].str);
      }
      else if (segmt[0].type == VAR && segmt[1].type == OP)
      {
        left = segmt[0].str;
        op = recognizeOp(segmt[1].str);
      }
      else
        success = false;

      if (success)
        success = unary_op(left, op);
			break;       
		case 3: //Binary operation or assignment
			if ((segmt[0].type != VAR && segmt[0].type != NUM)
       || (segmt[2].type != VAR && segmt[2].type != NUM))
      {
        success = false;
        break;
      }

      left = segmt[0].str;
      op = recognizeOp(segmt[1].str);
      right = segmt[2].str;
      
      if (op == ASN) //Assign
      {
        if (segmt[0].type != NUM) //1 + 2 is ok, 1 = 2 is not
          success = assign_op(left, right);
        else
          success = false;
      }
      else if (op == ADD || op == SUB || op == MULT || op == DIV) //Binary operation
        success = binary_op(left, op, right);
      else if (op == ADDASN) //Compound assignment:  a = a + b
        success = binary_assign_op(left, left, ADD, right);
      else if (op == SUBASN)
        success = binary_assign_op(left, left, SUB, right);
      else if (op == MULTASN)
        success = binary_assign_op(left, left, MULT, right);
      else if (op == DIVASN)
        success = binary_assign_op(left, left, DIV, right);
      else
        success = false;
      break;
		case 5: //Binary operation and assignment
      lhs = segmt[0].str;
      op = recognizeOp(segmt[1].str);
      if (segmt[0].type != VAR || op != ASN)
      {
        success = false;
        break;
      }

      left = segmt[2].str;
      op = recognizeOp(segmt[3].str);
      right = segmt[4].str;
      if (op == BAD_OP
        || (segmt[2].type != VAR && segmt[2].type != NUM)
        || (segmt[4].type != VAR && segmt[4].type != NUM))
      {
        success = false;
        break;
      }

			if (success)
				success = binary_assign_op(lhs, left, op, right); 
      break; 
    default:
      success = false;
		}
    //*/

    freeSegments(segmt);
	}
  else
    success = false;
  
	if (!success)
		cout << "Sorry, I do not understand." << endl;  
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
op_t recognizeOp(const char* op)
{
  if (strcmp(op, "=") == 0)
    return ASN;
  else if (strcmp(op, "+") == 0)
    return ADD;
  else if (strcmp(op, "-") == 0)
    return SUB;
  else if (strcmp(op, "*") == 0)
    return MULT;
  else if (strcmp(op, "/") == 0)
    return DIV;
  else if (strcmp(op, "++") == 0)
    return INC;
  else if (strcmp(op, "--") == 0)
    return DEC;
  else if (strcmp(op, "+=") == 0)
    return ADDASN;
  else if (strcmp(op, "-=") == 0)
    return SUBASN;
  else if (strcmp(op, "*=") == 0)
    return MULTASN;
  else if (strcmp(op, "/=") == 0)
    return DIVASN;
  else
    return BAD_OP;
}

// performs a binary operator assignment, such as " d = 6.28 * r";
// returns true if there is some error during the operation and false otherwise
// aka
// bool binary_assign(const char* assign_var, const char* left, OP operator, const char* right)

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right)
{
  double first, second, value;
  CVariable* assign;
  
  if (!getValue(left, first) || !getValue(right, second))
    return false;

  switch (op)
  {
  case ADD:
    value = first + second;
    break;
  case SUB:
    value = first - second;
    break;
  case MULT:
    value = first * second;
    break;
  case DIV:
    value = first / second;
    break;
  default:
    //cout << "Bad operator\n";
    return false;
  }

  assign = db->search(lhs);
  if (assign == NULL)
    db->addNew(lhs, value);
  else
    *assign = value;

  cout << lhs << " = " << value << endl;
  return true;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// performs a binary operator assignment, such as " d = 6.28 * r";
// returns true if there is some error during the operation and false otherwise
// aka binary_op(const char* left, OP operator, const char* right)
bool binary_op(const char* left, op_t op, const char* right)
{
  return binary_assign_op("ans", left, op, right);
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// performs a unary operator statement,like "x++";
// returns true if there is some error during the operation and false otherwise
// aka unary_op(const char* variable, OP unary_op)
bool unary_op(const char* operand, op_t op)
{
  CVariable* obj;

  obj = db->search(operand);
  if (obj == NULL)
    return false;

  switch (op)
  {
  case INC:
    (**obj)++;
    break;
  case DEC:
    (**obj)--;
    break;
  default:
    return false;
  }

  cout << operand << " = " << **obj << endl;
  return true;
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// performs a simple assignment statement, like "x = 1";
// returns true if there is some error in the assignment and false otherwise
// ... it was just called assign in lab5...
// aka assign(const char* lhs, const char* rhs)
bool assign_op(const char* lhs, const char* rhs)
{
  double value;
  CVariable* assign;

  if (!getValue(rhs, value))
    return false;

  assign = db->search(lhs);
  if (assign == NULL)
    db->addNew(lhs, value);
  else
    *assign = value;

  cout << lhs << " = " << value << endl;
  return true;
}


/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// evaluates a numeric string or variable name to its numeric value;
// returns true if expression is an invalid number or variable does not exist
// aka get_value(const char* expression, double& value)
bool getValue(const char* expr, double& value)
{
  //Try to read as a double
  istringstream iss(expr);
  iss >> value;
  if (iss) return true;
    //return true;

  //If that fails, search in DB
  CVariable* var = db->search(expr);
  if (var != NULL)
  {
    value = **var;
    return true;
  }
  //else
    return false;
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
/*bool IsAAsn(char* Buffer, int segmt[][2], char* res, char* operand)
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
}*/



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
/*bool IsABinary3(char* Buffer, int segmt[][2], char* operand_1, char* operand_2, OP& op)
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
    if(isAdd(piece[1]))                 // (strcmp(piece[1],"+")==0)
    {
        op = ADD;
        isValid = true; //Tag = true;
    }
    else if(isMinus(piece[1]))          // (strcmp(piece[1],"-")==0)
    {
        op = MIN;
        isValid = true; //Tag = true;
    }
    else if(isMult(piece[1]))           // (strcmp(piece[1],"*")==0)
    {
        op = MUL;
        isValid = true; //Tag = true;
    }
    else ifisDivide(piece[1])           // (strcmp(piece[1],"/")==0)
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
}*/

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

/*bool IsABinary5(char* Buffer, int segmt[][2], char* res , char* operand_1, char* operand_2, OP& op)
{
    bool isValid = false; // bool Tag = false;
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
            // Not sure what this does
            strcpy(res, piece[0]);
            strcpy(operand_1, piece[2]);
            strcpy(operand_2, piece[4]);
        }
    }
    
    return isValid; //Tag;
}*/

// explain operators (?? what does this mean..??)
/*void OpTranslator(OP op)
{
    switch(op)
    {
        case ASN: cout << "ASN"; break;
        case ADD: cout << "ADD"; break;
        case MIN: cout << "MIN"; break;
        case MUL: cout << "MUL"; break;
        case DIV: cout << "DIV"; break;
        case PRE_INC: cout << "PRE_INC";    break;
        case PRE_DEC: cout << "PRE_DEC";    break;
        case POST_INC: cout << "POST_INC";  break;
        case POST_DEC: cout << "POST_DEC";  break;
        default:
            cout << "UNRECOGNIZED OPERATOR";
            break;
    }
}*/





////////////////////////////////////////////////////////////////////////////////
// functions from MP#2
/*
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

*/



/*
 
 
 
 // if input is a letter - lizz version
 bool IsAChar(char str) { return ((str>='A'&&str<='Z')||(str>='a'&&str<='z')); }
 
 // if input is a digit - lizz version
 bool IsADigit(char str) { return ((str>='0'&&str<='9')||(str=='.')); }
 
 // if input is an operator - lizz version
 bool IsAOperator(char str)
 {
 return ((str=='+')||(str=='-')||(str=='*')||(str=='/')||(str=='='));
 }
 
 
 bool IsAChar(char str)
 {
 bool Tag = false;
 if((str>='A'&&str<='Z')||(str>='a'&&str<='z')) Tag = true;
 return Tag;
 
 }
 
 bool IsADigit(char str)
 {
 bool Tag = false;
 if((str>='0'&&str<='9')||(str=='.')) Tag = true;
 return Tag;
 
 }
 
 bool IsAOperator(char str)
 {
 bool Tag = false;
 if((str=='+')||(str=='-')||(str=='*')||(str=='/')||(str=='=')) Tag = true;
 return Tag;
 
 }


 // i made these for readability of code but they're not necessary
 // especially since the body is so short
bool isEquals(char* piece) {return (strcmp(piece,"=") == 0);}
bool isAdd(char* piece) {return (strcmp(piece,"+") == 0);}
bool isMinus(char* piece) {return (strcmp(piece,"-") == 0);}
bool isMult(char* piece) {return (strcmp(piece,"*") == 0);}
bool isDivide(char* piece) {return (strcmp(piece,"/") == 0);}
bool isInc(char* piece) {return (strcmp(piece, "++") == 0); }
bool isDec(char* piece) {return (strcmp(piece, "--") == 0); }
 */

