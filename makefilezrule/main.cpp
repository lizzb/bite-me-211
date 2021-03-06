/*

Lets put a nicer description here someday


*/

//#include "stdafx.h" // in lab 3, not 2 4 or 5

#include <iostream> // main4 and 5 and 3 and 2
#include <fstream>  // main 2 and 3
#include <sstream>
#include <string>   // main4 and 5 and 3 and 2
#include <string.h>

#include "CMatrix.h" // pretty sure this isnt necessary but iono
#include "CVariable.h"
using namespace std; 

#define INPUT_FILE "lizzTests.txt" 
//"lab6TestCases.txt" //"TestCasesForBuild.txt" //lab5TestCase.txt"

// lab 3
//enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC};
// enumeration of operator types

// //  OP  op;  was previous enum type assuming that caused issues
enum op_t  {ASN, ADD, SUB, MULT, DIV, INC, DEC, ADDASN, SUBASN, MULTASN, DIVASN, BAD_OP}; 
enum seg_t {VAR, NUM, MAT, OP, BAD_SEG};

op_t recognizeOp(const char* op);
// void OpTranslator(OP); // output the operator // lab 3


typedef struct
{
  char* str;
  seg_t type;
} segment_t;

  // Database for holding variables // lab 5
CVarDB* db; 

// function declarations //
void interpreter(const char* cmd);
bool partitioner(const char* cmd, segment_t** segmt, int& numseg);
void freeSegments(segment_t* segmt);



  bool isChar(char c);      // if input is a letter
  bool isDigit(char c);     // if input is a digit 
  bool isOp(char c);  // if input is an operator
  bool isSpace(char c);     // if input is a space

//void Interpreter(string&); // lab 3 version
// partitioning the command line into segments
// int Partitioner(char*, int [][2], int&); // lab 3 version
// function Patitioner(Buffer) // lab 2 version
// returns 1 when the parsing is completed
// and the segments are printed on screen.
// returns 0 when the input command line is not valid.      

// lab 2+3

// if the command line is valid unary operation // lab 2+3
//bool IsAUnary(char*, int [][2], char*, OP&); // lab 2+3
  bool unary_op(const char* operand, op_t op);  

// if the command line is a valid assignment // lab 2+3
//bool IsAAsn(char*, int [][2], char*, char*); // lab 2+3
  bool assign_op(const char* lhs, const char* rhs); 

// if the command line is a valid binary operation // lab 2+3
//bool IsABinary3(char*, int [][2], char*, char*, OP&);  // lab 2+3
  bool binary_op(const char* left, op_t op, const char* right);  

// if the command line is a valid assignment and binary operation // lab 2+3
//bool IsABinary5(char*, int [][2], char*, char*, char*, OP&); // lab 2+3
  bool binary_assign_op(const char* lhs, const char* left, op_t op, const char* right);  

  bool getValue(const char* expr, double& value);

ostream& operator<<(std::ostream& out, CMatrix& m);

  void add(CVariable& cvar);

  int main()
  {
    // print welcome message
    cout << endl;
    cout << "\tWelcome to the EECS 211 MP#6: Death" << endl;
    cout << "\t\tYour Name, Northwestern University "<< endl;
    cout << "\t\t   Copyright, 2014   " << endl;   

  db = new CVarDB();  // lab 5

  // Get the input
  string currentline; //cmd lab 5   // string Buffer; // lab 2 3
  // int num_Case=0; // lab 2 3

  // ifstream TestFile("TestCase.txt"); // read from file lab 2 3
  ifstream TestFile(INPUT_FILE);   // read from file // better name than "in"

  cout << "\tWelcome to EECS 211 Lab 5:  Programmable Calculator" << endl; 
  cout << "\tWilliam Hendrix, Northwestern University "<< endl; 
  cout << "\tCopyright 2014   " << endl;    


  // Open file
  if (TestFile.is_open())
  {
    // read a command line
    while (getline(TestFile, currentline))
    {
      // Special commands:  quit and who

      // if the input is 'quit'
      if (currentline == "quit") //if (Buffer.compare("quit")==0) 
      {
        //cout << "\nThank you. "; //quit the program
        cout << "Thank you. Now closing...\n";  
        break;
      }

      else if (currentline == "who")
      {
        // lines make it easier to distinguish in output
        cout << "--------WHO---------" << endl;
        cout << *db;
        cout << "--------------------" << endl;
        continue; 
      }

      // Otherwise, interpret and run the command normally
      else // no else for lab 5
      {
        // print the command line
        //cout << "\n# " << ++num_Case <<" : "<< Buffer << endl; 

        // process the command line
        interpreter(currentline.c_str());  // lab 5
        //Interpreter(Buffer); // lab 3, not 2
      }
    }

    TestFile.close();
  }

  // Otherwise the file failed to open
  else cout << "Unable to open input file " << INPUT_FILE << endl;  

  // delete the database of variables
  delete db;  

  return 0;  
}





























/* ----------------------------------------------------------------------------
 Name:     unary_op
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool unary_op(const char* operand, op_t op)
 {
  CVariable* obj;

  obj = db->search(operand);
  if (obj == NULL) return false;

  switch (op)
  {
    case INC: (**obj)++; break;
    case DEC: (**obj)--; break;
    default:
    return false;
  }

  cout << operand << " = " << **obj << endl;
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
  double value;
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
  double first, second, value;
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
 bool getValue(const char* expr, double& value)
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
  }
  else return false;
}


/* ----------------------------------------------------------------------------
 Name:     
 Purpose: output a matrix via the << operator (rather than printMatrix function)
 ---------------------------------------------------------------------------- */
ostream& operator<<(std::ostream& out, CMatrix& m)
{

  if (m.isNull()) out << "\tnull matrix" << endl;
  else
  {
    // row by row
    for (int i = 0; i < m.getNRow(); ++i)
    {
      out << "\t";
      for (int j = 0; j < m.getNCol(); ++j)
        out << m.element(i, j) << "\t";

      out << endl;
    }
  }
  out << endl;
  return out;
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

/* LAB 23
// explain operators
void OpTranslator(OP op) 
{
  switch(op){
  case ASN:   cout << "ASN" ; break;
  case ADD:   cout << "ADD" ; break;
  case MIN:   cout << "MIN" ; break;
  case MUL:   cout << "MUL" ; break;
  case DIV:   cout << "DIV" ; break;
  case PRE_INC:   cout << "PRE_INC" ; break;
  case PRE_DEC: cout << "PRE_DEC" ; break;
  case POST_INC:  cout << "POST_INC"; break;
  case POST_DEC:  cout << "POST_DEC"; break;
  default:
    cout << "UNRECOGNIZED OPERATOR" ;   break;
  }
}
*/

/* ----------------------------------------------------------------------------
 Name:     isType functions
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------
 Name:     isChar
 Returns:  
 ---------------------------------------------------------------------------- */
 bool isChar(char c)
 {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
  else return c == '_'; // this is the only other acceptable character
  // finally understand why this returns c=='_'
  // rather than a plain true or false

  //  return ((c >= 'A' && c <= 'Z') || (c >= 'a'&& c <= 'z')); // lab 2+3
}


/* ----------------------------------------------------------------------------
 Name:     isDigit
 Returns:  
 ---------------------------------------------------------------------------- */
 bool isDigit(char c)
 {
  if (c >= '0' && c <= '9') return true;
  else return c == '.'; // only other acceptable character to be considered a digit
  // oh wow i get it this will return true if its a decimal
  // (ie still part of a number)
  // and otherwise false
  // that is SO NOT OBVIOUS

  //  return ((c >= '0' && c <= '9')|| (c =='.')); // lab 2+3
}



/* ----------------------------------------------------------------------------
 Name:     isOp
 Returns:  
 ---------------------------------------------------------------------------- */
 bool isOp(char c)
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
  // return ((c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='=')); // lab 2+3
}


/* ----------------------------------------------------------------------------
 Name:     isSpace
 Returns:  
 ---------------------------------------------------------------------------- */
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





////////////////////////////////////////////////////////////////////////////////
// functions related to the command line interpreter

// void Interpreter(string& Input) // lab 3
// int Partitioner(char* Buffer,  int segmt[][2], int& iSeg) // lab 3
// bool Partitioner(string& Input) // lab 2
/* ----------------------------------------------------------------------------
 Name:     interpreter
 Purpose:  MAGIC
 Params:   
 Returns:  not sure if should edit this one or partitioner to recognize matrices
 ----------------------------------------------------------------------------*/ 
 void interpreter(const char* cmd)
 {
  /* // lab 3 or 2+3
  char Buffer[500]; // array buffer to hold the command line
  strncpy(Buffer, Input.c_str(), sizeof(Buffer));
  Buffer[sizeof(Buffer) - 1] = 0;

  // indicator LAB 3
  int st=0; // start point
  int ed=0; // end point

  // int segmt[10][2]; // record the location of each segment (lab 3 comment)
  // the location of each segment: start point, length (lab 2 comment)

  */


   //char buffer[500];
  segment_t* segmt;

  // result_name, operand_1 and operand_2 (lab3 comment)
  //char res[50], operand_1[50], operand_2[50]; 
  char* lhs;
  char* left;
  char* right;

  // the operator in the command line
  op_t op; 

  // number of segments in command line
  int numSeg;

  // (previous labs called it iSeg)
  //int iSeg = 0; 
  // type asn:   e.g., a = b              (iSeg = 3)
  // type unary: e.g., a++                (iSeg = 2)
  // type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)

   // aka error_code = 1 or true or Tag or isValid = false in previous labs
  bool success; 


  //*****************************************************//
  // if the command line can be successfully segment
  // if(Partitioner(Buffer,segmt,iSeg))
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

    success = true; // if(error_code == 1)
    cout << cmd << endl;

    // valid cases can be : 2, 3 or 5 // switch (iSeg) 
    // Must have 2, 3, or 5 segments
    switch (numSeg) 
    {

      // the command line is possible to be unary operation
      // Unary operation
      case 2: 
      {
        // cout << "case 2";
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

        /*
        // if it is a valid unary operation
        Tag = IsAUnary(Buffer,segmt,operand_1,op); 
        if(Tag)
        {   // it is a valid unary operation, output the result
          OpTranslator(op); 
          cout << " " << operand_1 << endl;
        }  
        break;  
        */      
      }

    // Binary operation or assignment
    // the command line is possible to be binary operation or assignment
      case 3: 
      {
      if ((segmt[0].type != VAR && segmt[0].type != NUM)
       || (segmt[2].type != VAR && segmt[2].type != NUM))
      {
        success = false;
        break;
      }

      left = segmt[0].str;
      op = recognizeOp(segmt[1].str);
      right = segmt[2].str;

      // if it is a valid assignment
      if (op == ASN) //Assign
      {
        // it is a valid assignment, output the result
        if (segmt[0].type != NUM) //1 + 2 is ok, 1 = 2 is not
          success = assign_op(left, right);
        else success = false;
      }
      /*
        if(IsAAsn(Buffer,segmt,res,operand_1)) // if it is a valid assignment
        {   // it is a valid assignment, output the result
          Tag = true;
          cout << "ASN " << " " << operand_1 << " to " << res <<endl;
        }
        */
        /*
        else if(IsABinary3(Buffer,segmt,operand_1,operand_2,op)) // if it is a binary operation with assignment to default variable ans
        {   // it is a binary operation, output the result
          Tag = true;
          OpTranslator(op);
          cout << " " << operand_1 << " AND " << operand_2 << " , THEN ASN to ans. " << endl;
        }
        break;
        */
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

    }
    // the command line is possible to be binary operation and assignment
    case 5: //Binary operation and assignment
    //cout << "case 5";
    /*
    // if it is a binary operation with assignment to a specified variable
        Tag = IsABinary5(Buffer,segmt,res,operand_1,operand_2,op); 
        if(Tag)
        {   // it is a binary operation, output the result
          OpTranslator(op);
          cout<<" "<<operand_1<<" AND "<<operand_2<<" , THEN ASN to "<< res <<endl;
        }  
        break; 
        */  
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

  freeSegments(segmt);
}


else success = false;

// if the command line is not valid
if (!success)
  cout << "Sorry, I do not understand." << endl;  

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
 Purpose:  MYSTERIOUS MAGIC DON'T EDIT - at least not first loop don't think
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
 bool partitioner(const char* cmd, segment_t** segmt, int& numseg)
 {
  // pos - keeps track of the position in the "string" which is really
  // a pointer to an aray of chars

  int count;
  char* buffer;
  //char curr; //c current character
  int bpos;

  //
  // First loop:  input checking and segment counting
  //

  int pos = 0;
  int i = 0; // using i instead of pos because its shorter
  numseg = 0;

  // ------------------------------------------------------
  // begin partitioner 


  // get the length of command line
  int len = strlen(cmd);

  while (i < len) // while (pos < len)
  {
    // the current character at this position
    //curr = cmd[pos]; //c = cmd[pos];

    

    // Whitespace
    if (isSpace(cmd[i])) 
    {
      i++;
      continue; //Don't advance to next segment!
    }

    // Variable name

    // check consecutive characters
    else if (isChar(cmd[i]))  // if(IsAChar(Buffer[st])) //isChar(c) 
    {
      i++;
      // Oh WOW this is to enforce the convention/limitation/whatever
      // that variables can't start with a number
      // Characters after the first are allowed to be 0-9... at least i think
      while ( (i < len) && 
              ((isChar(cmd[i]) || 
                (cmd[i] >= '0' && cmd[i] <= '9'))) )
        i++;
      // while( (ed<len)&&(IsAChar(Buffer[ed]) || IsADigit(Buffer[ed]) || Buffer[ed]=='_')) ed++;
    }

    // Negative number or operator
    else if (cmd[i] == '-')  
    {
      i++;
      // Negative number
      if (i < len && isDigit(cmd[i])) while (i < len && isDigit(cmd[i])) i++;

      // Operator
      else if (i < len && isOp(cmd[i]))while (i < len && isOp(cmd[i])) i++;
    }

    // Operator
    else if (isOp(cmd[i])) 
    {
      i++;
      while (i < len && isOp(cmd[i])) i++;
    }

    // Scalar
    else if (isDigit(cmd[i]))
    {
      i++;
      while (i < len && isDigit(cmd[i])) i++;
    }

    // Matrix

    // check matrix
      else if((cmd[i]=='['))  
      {
        i++;
        while( (i < len) && (cmd[i]!=']') )
        {
          if(isDigit(cmd[i])||(cmd[i]==',')||(cmd[i]==';')||(cmd[i]==' ')||(cmd[i]=='.'))
          {
            i++;
          }
          else
          {
            //cout<<"Expect a ']' here."<<endl;
            // dont need to print this but the ] will be added
            //error_code = 0;// error_code = false; // lab 2
            break;
          }
          i++;
        }
      }
      
      //lab5: We'll check matrix validity in CMatrix (Lab 6)
      //We won't worry about it here
      //pos++; //Skip over ']'

      //getRowCol //FillArray // i think these are called within cmatrix

      //GetRowCol(matrixdata, r, c);
      //FillArray(str, m_aData, m_nRow*m_nCol);
      // FillArray should not return false since we checked that with GetRowCol

    // Unrecognized case
    else return false;
    numseg++;
  }

// Macro function to make code easier to read
#define push_to_buffer() {buffer[bpos] = cmd[pos]; pos++; bpos++;}

  // 
  // Second loop:  populating segmt structure
  // 
  *segmt = new segment_t[numseg];
  buffer = new char[len + numseg];

  bpos = pos = count = 0;

  while (pos < len)
  {
    (*segmt)[count].str = &buffer[bpos]; // Segment count starts at this position
    //c = cmd[pos];

    // VARIABLE NAME
    if (isChar(cmd[pos])) //Variable
    {
      (*segmt)[count].type = VAR;

      //Characters after the first are allowed to be 0-9
      while (pos < len && (isChar(cmd[pos]) || (cmd[pos] >= '0' && cmd[pos] <= '9')))  push_to_buffer();
    }
    else if (cmd[pos] == '-')  //Negative number or operator
    {
      buffer[bpos] = '-';
      pos++;
      bpos++;

      // NEGATIVE 
      if (pos < len && isDigit(cmd[pos])) //Negative number
      {
        (*segmt)[count].type = NUM;
        while (pos < len && isDigit(cmd[pos])) push_to_buffer();
      }
      else //Operator
      {
        (*segmt)[count].type = OP;
        while (pos < len && isOp(cmd[pos])) push_to_buffer();
      }
    }

    // OPERATOR
    else if (isOp(cmd[pos])) // Operator
    {
      (*segmt)[count].type = OP;
      while (pos < len && isOp(cmd[pos])) push_to_buffer();
    }

    // SCALAR
    else if (isDigit(cmd[pos])) //Scalar
    {
      (*segmt)[count].type = NUM;
      while (pos < len && isDigit(cmd[pos])) push_to_buffer();
    }

    // MATRIX
    else if (cmd[pos] == '[') // Matrix
    {
      //cout << "recognized [ in secon dloop";
      (*segmt)[count].type = MAT;
      //cout << "labeled the type Matrix";
      while (pos < len && cmd[pos] != ']')
        {
          push_to_buffer();
          //cout << "kept going" <<endl;
        }

      //Add ']' to buffer, as well
      push_to_buffer();
    }
    else if (isSpace(cmd[pos])) //Whitespace
    {
      pos++;
      continue; // Don't advance to next segment!
    }
    else // Should never execute
    {
      delete buffer;
      delete segmt;
      return false;
    }
    
    buffer[bpos] = '\0';  // Null-terminate this segment
    bpos++;
    count++; // Advance to next segment
  }

  return true;
}







/* ----------------------------------------------------------------------------
 Name:     printMatrix
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- 
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
}*/


/*
// If the input command line is a valid unary operation
// Input:
// char* Buffer   : the input command line (known)
// int segmt[][2] : the location of each segment in the command line (known)
// char* operand  : the operand in the command line (to fill in)
// OP& op         : the operator (to fill in)
// Output:
// boolean variable : 0 -- not a valid unary operation, 1 -- valid unary operation
bool IsAUnary(char* Buffer, int segmt[][2], char* operand, OP& op)
{
  bool Tag = false;
  char piece[2][50];
  for (int i = 0 ; i<2; i++)
  {
    for(int j = 0; j<segmt[i][1]; j++)
    {
      piece[i][j] = Buffer[j+segmt[i][0]];
    }
    piece[i][segmt[i][1]] = '\0';
  }
  if(strcmp(piece[0],"++")==0)
  {
    op = PRE_INC;
    strcpy(operand, piece[1]);
    Tag = true;
  }
  else if (strcmp(piece[0],"--")==0)
  {
    op = PRE_DEC;
    strcpy(operand, piece[1]);
    Tag = true;
  }
  else if(strcmp(piece[1],"++")==0)
  {
    op = POST_INC;
    strcpy(operand, piece[0]);
    Tag = true;
  }
  else if (strcmp(piece[1],"--")==0)
  {
    op = POST_DEC;
    strcpy(operand, piece[0]);
    Tag = true;
  }

  return Tag;
}*/
/*
// If the input command line is a valid assignment
// Input:
// char* Buffer   : the input command line (known)
// int segmt[][2] : the location of each segment in the command line (known)
// char* res      : the reseult_name in the command line (to fill in)
// char* operand  : the operand in the command line (to fill in)
// Output:
// boolean variable : 0 -- not a valid assignment, 1 -- valid assignment

bool IsAAsn(char* Buffer, int segmt[][2], char* res, char* operand)
{
  bool Tag = false;
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
    Tag = true;
  }
  return Tag;
}*/


  /*
// If the input command line is a binary operation
// Input:
// char* Buffer   : the input command line (known)
// int segmt[][2] : the location of each segment in the command line (known)
// char* operand_1: the operand_1 in the command line (to fill in)
// char* operand_2: the operand_2 in the command line (to fill in)
// OP& op         : the operator (to fill in)
// Output:
// boolean variable : 0 -- not a valid binary operation, 1 -- valid binary operation
bool IsABinary3(char* Buffer, int segmt[][2], char* operand_1, char* operand_2, OP& op)
{
  bool Tag = false;
  char piece[3][50];
  for (int i = 0 ; i<3; i++)
  {
    for(int j = 0; j<segmt[i][1]; j++)
    {
      piece[i][j] = Buffer[j+segmt[i][0]];
    }
    piece[i][segmt[i][1]] = '\0';
  }
  if(strcmp(piece[1],"+")==0) // if the #2 piece is an operator
  {
    op = ADD;
    Tag = true;
  }
  else if(strcmp(piece[1],"-")==0)
  {
    op = MIN;
    Tag = true;
  }
  else if(strcmp(piece[1],"*")==0)
  {
    op = MUL;
    Tag = true;
  }
  else if(strcmp(piece[1],"/")==0)
  {
    op = DIV;
    Tag = true;
  }
  if (Tag)
  {
    strcpy(operand_1, piece[0]);
    strcpy(operand_2, piece[2]);
  }
  return Tag;
}*/

/*
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
  bool Tag = false;
  char piece[5][50];
  for (int i = 0 ; i<5; i++)
  {
    for(int j = 0; j<segmt[i][1]; j++)
    {
      piece[i][j] = Buffer[j+segmt[i][0]];
    }
    piece[i][segmt[i][1]] = '\0';
  }
  if(strcmp(piece[1],"=")==0) // if the #2 piece is "=" 
  {
    if(strcmp(piece[3],"+")==0) // if the #4 piece is an operator 
    {
      op = ADD;
      Tag = true;
    }
    else if(strcmp(piece[3],"-")==0)
    {
      op = MIN;
      Tag = true;
    }
    else if(strcmp(piece[3],"*")==0)
    {
      op = MUL;
      Tag = true;
    }
    else if(strcmp(piece[3],"/")==0)
    {
      op = DIV;
      Tag = true;
    }
    if (Tag)
    {
      strcpy(res, piece[0]);
      strcpy(operand_1, piece[2]);
      strcpy(operand_2, piece[4]);
    }
  }

  return Tag;
}*/


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

Lab 3 Interpreter
// EECS 211 MP#2: A Command Line Interpretation
// This project is to  
// Resolve a command line by checking the grammar of the command
// and explain the command line 
 */