/* ----------------------------------------------------------------------------

Based off Lab 5 Sample Solution

wow i love how thorough the commenting is so that the professor can clear up
any misconceptions or common mistakes the students had... -_-

... i'm also loving all of the SUPER subtle changes to names that could have
students wondering why nothing will compile...

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

enum op_t  {ASN, ADD, SUB, MULT, DIV, INC, DEC, ADDASN, SUBASN, MULTASN, DIVASN, BAD_OP}; 
enum seg_t {VAR, NUM, MAT, OP, BAD_SEG};

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

void interpreter(const char* cmd);

op_t recognizeOp(const char* op);
bool partitioner(const char* cmd, segment_t** segmt, int& numseg);
void freeSegments(segment_t* segmt);

bool isChar(char c);
bool isDigit(char c);
bool isOperator(char c);
bool isSpace(char c);

bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right);  
bool binary_op(const char* left, op_t op, const char* right);  
bool unary_op(const char* operand, op_t op);  
bool assign_op(const char* lhs, const char* rhs);  
bool getValue(const char* expr, double& value);  

void add(CVariable& cvar);

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
}

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

void freeSegments(segment_t* segmt)
{
  delete segmt[0].str;
  delete segmt;
}

bool isChar(char c)
{
  if (c >= 'a' && c <= 'z')
    return true;
  else if (c >= 'A' && c <= 'Z')
    return true;
  else
    return c == '_';
}

bool isDigit(char c)
{
  if (c >= '0' && c <= '9')
    return true;
  else
    return c == '.';
}

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

bool isSpace(char c)
{
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

// performs a binary operator assignment, such as " d = 6.28 * r";
// returns true if there is some error during the operation and false otherwise
// aka binary_op(const char* left, OP operator, const char* right)
bool binary_op(const char* left, op_t op, const char* right)
{
  return binary_assign_op("ans", left, op, right);
}

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


// evaluates a numeric string or variable name to its numeric value;
// returns true if expression is an invalid number or variable does not exist
// aka get_value(const char* expression, double& value)
bool getValue(const char* expr, double& value)
{
  //Try to read as a double
  istringstream iss(expr);
  iss >> value;
  if (iss)
    return true;

  //If that fails, search in DB
  CVariable* var = db->search(expr);
  if (var != NULL)
  {
    value = **var;
    return true;
  }
  else
    return false;
}
