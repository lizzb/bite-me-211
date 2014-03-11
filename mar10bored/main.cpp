/**

 Lab 5:  a Programmable Calculator

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

#include <iostream> // main4 and 5
#include <fstream>
#include <sstream>
#include <string>   // main4 and 5
#include <string.h>

#include "CMatrix.h"
#include "CVariable.h"
using namespace std; 

#define INPUT_FILE "TestCasesForBuild.txt" //lab5TestCase.txt"

   enum op_t  {ASN, ADD, SUB, MULT, DIV, INC, DEC, ADDASN, SUBASN, MULTASN, DIVASN, BAD_OP}; 
   enum seg_t {VAR, NUM, MAT, OP, BAD_SEG};

   typedef struct
   {
    char* str;
    seg_t type;
  } segment_t;

  CVarDB* db; 

  void interpreter(const char* cmd);
  bool partitioner(const char* cmd, segment_t** segmt, int& numseg);
  void freeSegments(segment_t* segmt);


  op_t recognizeOp(const char* op);
  bool isChar(char c);
  bool isDigit(char c);
  bool isOperator(char c);
  bool isSpace(char c);

  
  bool unary_op(const char* operand, op_t op);  
  bool assign_op(const char* lhs, const char* rhs);  
  bool binary_op(const char* left, op_t op, const char* right);  
  bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right);  

  bool getValue(const char* expr, CMatrix& value); //double& value);  

  void add(CVariable& cvar);

  int main()
  {

  // print welcome message
    cout << endl;
    cout << "\tWelcome to the EECS 211 MP#4: CMatrix Classes" << endl;
    cout << "\t\tYour Name, Northwestern University "<< endl;
    cout << "\t\t   Copyright, 2014   " << endl;   

    /*
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
    printMatrix(m2);

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
  */
  //cout << "Press any key to end...";
  //cin.get();  // wait for a key to end your program


  db = new CVarDB();  

  // Get the input
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

      // Otherwise, interpret and run the command normally
      interpreter(cmd.c_str()); 
    }

    in.close();  
  }

  delete db;  
  //char c;  
  //cout << "Type 'q' to quit: ";  
  //cin >> c;  


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
quit

*/


return 0;  
}




/* ----------------------------------------------------------------------------
 Name:     interpreter
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 void interpreter(const char* cmd)
 {
   //char buffer[500];
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

    // Must have 2, 3, or 5 segments
		switch (numSeg) 
		{

    // Unary operation
		case 2: 
    cout << "case 2";
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
    else success = false;

    if (success) success = unary_op(left, op);
    break;       

    // Binary operation or assignment
		case 3: 
   if ((segmt[0].type != VAR && segmt[0].type != NUM)
     || (segmt[2].type != VAR && segmt[2].type != NUM))
   {
    cout << "case 3";
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
        else success = false;
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
      
      else success = false;
      break;


		case 5: //Binary operation and assignment
    cout << "case 5";
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

    if (success) success = binary_assign_op(lhs, left, op, right); 
    break; 
    default: success = false;
  }
    //*/

  freeSegments(segmt);
}
else success = false;

if (!success) cout << "Sorry, I do not understand." << endl;  
}


/* ----------------------------------------------------------------------------
 Name:     freeSegments
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
 Name:     partitioner
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool partitioner(const char* cmd, segment_t** segmt, int& numseg)
 {
  // pos - keeps track of the position in the "string" which is really
  // a pointer to an aray of chars
  int pos, len, bpos, count;
  char* buffer;
  char c;

  //First loop:  input checking and segment counting
  pos = numseg = 0;
  len = strlen(cmd);
  while (pos < len)
  {
    c = cmd[pos];

    // Variable name
    if (isChar(c)) 
    {
      pos++;
      // Oh WOW this is to enforce the convention/limitation/whatever
      // that variables can't start with a number
      // Characters after the first are allowed to be 0-9
      while (pos < len && (isChar(cmd[pos]) || (cmd[pos] >= '0' && cmd[pos] <= '9'))) pos++;
    }

    // Negative number or operator
    else if (c == '-')  
    {
      pos++;
      // Negative number
      if (pos < len && isDigit(cmd[pos])) 
        while (pos < len && isDigit(cmd[pos])) pos++;

      // Operator
      else if (pos < len && isOperator(cmd[pos]))
        while (pos < len && isOperator(cmd[pos])) pos++;
      }

    // Operator
    else if (isOperator(c)) 
    {
      pos++;
      while (pos < len && isOperator(cmd[pos])) pos++;
    }

    // Scalar
    else if (isDigit(c))
    {
      pos++;
      while (pos < len && isDigit(cmd[pos])) pos++;
    }
    else if (c == '[') //Matrix
    {
      char *matrixdata = new char[500]; // = '[';
      //getRowCol
      //FillArray

      pos++;
      //We'll check matrix validity in CMatrix (Lab 6)
      //We won't worry about it here
      int i = 0;
      matrixdata[i] = '[';
      int r;
      int c;
      while (pos < len && cmd[pos] != ']')
      {
        i++;
        //cout << cmd[pos] << endl;
        matrixdata[i] = cmd[pos];
        
        
        //GetRowCol(const char *str, int &nRow, int &nCol)
         // cout << (cmd[pos]); //pos++; logic here for understanding matrix rather than skipping
        pos++;
      }
      i++;
      matrixdata[i] = ']';
      
      pos++; //Skip over ']'
  
      cout << matrixdata << endl;
      CMatrix m1(matrixdata);

      printMatrix(m1);
      //GetRowCol(matrixdata, r, c);
      //FillArray(str, m_aData, m_nRow*m_nCol);
  // FillArray should not return false since we checked that with GetRowCol
}
    // Whitespace
    else if (isSpace(c)) 
    {
      pos++;
      continue; //Don't advance to next segment!
    }
    // Unrecognized case
    else return false;
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
 Name:     unary_op
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool unary_op(const char* operand, op_t op)
 {
    return false; /// skip

  CVariable* obj;

  obj = db->search(operand);
  if (obj == NULL) return false;

  switch (op)
  {
    //case INC: (**obj)++; break;
    //case DEC: (**obj)--; break;
    default:
    return false;
  }

  //cout << operand << " = " << **obj << endl;
  return true;
}

/* ----------------------------------------------------------------------------
 Name:     assign_op
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool assign_op(const char* lhs, const char* rhs)
 {
  CMatrix value; //double value;
  CVariable* assign;

  if (!getValue(rhs, value)) return false;

  assign = db->search(lhs);
  if (assign == NULL) db->addNew(lhs, value);
  else *assign = value;

  cout << lhs << " = " << value << endl;
  return true;
}


/* ----------------------------------------------------------------------------
 Name:     binary_assign_op
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right)
 {
  CMatrix first, second, value; //double first, second, value;
  CVariable* assign;
  
  if (!getValue(left, first) || !getValue(right, second)) return false;

  switch (op)
  {
    case ADD: value = first + second; break;
    case SUB: value = first - second; break;
    case MULT: value = first * second; break;
    case DIV: value = first / second; break;
    default:
    //cout << "Bad operator\n";
    return false;
  }

  assign = db->search(lhs);
  if (assign == NULL) db->addNew(lhs, value);
  else *assign = value;

  cout << lhs << " = " << value << endl;
  return true;
}


/* ----------------------------------------------------------------------------
 Name:     binary_op
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool binary_op(const char* left, op_t op, const char* right)
 {
  return binary_assign_op("ans", left, op, right);
}


/* ----------------------------------------------------------------------------
 Name:     getValue
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool getValue(const char* expr, CMatrix& value) //double& value)
 {
  //Try to read as a double
  istringstream iss(expr);
  iss >> value;
  if (iss) return true; // dont know what this is doing

  //If that fails, search in DB
  CVariable* var = db->search(expr);
  if (var != NULL)
  {
    value = **var;
    return true;
    //return false;
  }
  else return false;
}






/* ----------------------------------------------------------------------------
 Name:     recognizeOp
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 op_t recognizeOp(const char* op)
 {
  if (strcmp(op, "=") == 0) return ASN;
  else if (strcmp(op, "+") == 0) return ADD;
  else if (strcmp(op, "-") == 0) return SUB;
  else if (strcmp(op, "*") == 0) return MULT;
  else if (strcmp(op, "/") == 0) return DIV;
  else if (strcmp(op, "++") == 0) return INC;
  else if (strcmp(op, "--") == 0) return DEC;
  else if (strcmp(op, "+=") == 0) return ADDASN;
  else if (strcmp(op, "-=") == 0) return SUBASN;
  else if (strcmp(op, "*=") == 0) return MULTASN;
  else if (strcmp(op, "/=") == 0) return DIVASN;
  else
    return BAD_OP;
}


/* ----------------------------------------------------------------------------
 Name:     isType functions
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */

 bool isChar(char c)
 {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
  else return c == '_'; // still don't understand why returns a char not bool?
}

bool isDigit(char c)
{
  if (c >= '0' && c <= '9') return true;
  else return c == '.'; // still don't understand why returns a char not bool?
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



/* ----------------------------------------------------------------------------
 Name:     printMatrix
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
void printMatrix(CMatrix &m)
{
  if (m.isNull())
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


ostream& operator<<(ostream& out, CVariable& cvar)
{
  return out << cvar.name << ":\t";// << printMatrix(cvar.value); // edit
  printMatrix(cvar.value);
}

ostream& operator<<(ostream& out, CVarDB& cdb)
{
  cout << "Variables: \n";
  int len = cdb.db.size();
  for (int i = 0; i < len; i++)
    out << cdb.db[i] << endl;
  return out;
}