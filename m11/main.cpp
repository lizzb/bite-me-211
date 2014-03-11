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

//#include "stdafx.h" // in lab 3, not 2 4 or 5

#include <iostream> // main4 and 5 and 3 and 2
#include <fstream>  // main 2 and 3
#include <sstream>
#include <string>   // main4 and 5 and 3 and 2
#include <string.h>

#include "CMatrix.h"
#include "CVariable.h"
using namespace std; 

#define INPUT_FILE "TestCasesForBuild.txt" //lab5TestCase.txt"

// lab 3
//enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC};
// enumeration of operator types
// void OpTranslator(OP); // output the operator // lab 3

enum op_t  {ASN, ADD, SUB, MULT, DIV, INC, DEC, ADDASN, SUBASN, MULTASN, DIVASN, BAD_OP}; 
enum seg_t {VAR, NUM, MAT, OP, BAD_SEG};

op_t recognizeOp(const char* op);


typedef struct
{
  char* str;
  seg_t type;
} segment_t;

  // Database for holding variables // lab 5
CVarDB* db; 



// functions from the previous project // as in lab 3
// int Partitioner(char*, int [][2], int&);
// partitioning the command line into segments

void interpreter(const char* cmd);
bool partitioner(const char* cmd, segment_t** segmt, int& numseg);
void freeSegments(segment_t* segmt);



  bool isChar(char c);      // if input is a letter
  bool isDigit(char c);     // if input is a digit 
  bool isOperator(char c);  // if input is an operator
  bool isSpace(char c);     // if input is a space

// lab 2+3
//bool IsAChar(char);
//bool IsADigit(char); 
//bool IsAOperator(char);
// LAB 2
// function Patitioner(Buffer) returns 1 when the parsing is completed.
// And the segments are printed on screen.
// function Patitioner(Buffer) returns 0 when the input command line is not valid.      


//function declaration
// lab 2+3

//void Interpreter(string&); // lab 3

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

  void add(CVariable& cvar);

  int main()
  {
    // print welcome message
    cout << endl;
    cout << "\tWelcome to the EECS 211 MP#6: Death" << endl;
    cout << "\t\tYour Name, Northwestern University "<< endl;
    cout << "\t\t   Copyright, 2014   " << endl;   

    /* from lab3 i think or 4
    CMatrix
    null, // null one
    m1(1.1), // 1 by 1 matrix with element 1.1
    m2(2, 2), // 2 by 2 zero matrix
    mstr("[1.2 3.4 5.6; 2.1 4.3 6.5]"), // matrix from string
    merr("[1.2 3.4 5.6; 2.1]"); // bad input
    cout << "A null matrix:" << endl; printMatrix(null);
    cout << "An 1 by 1 matrix:" << endl; printMatrix(m1);
    cout << "A 2 by 2 matrix:" << endl; printMatrix(m2);
    cout << "A 2 by 3 matrix:" << endl; printMatrix(mstr);
    cout << "A invalid matrix:" << endl; printMatrix(merr);
    cout << "Resize to 3 by 4:" << endl;
    mstr.resize(3, 4); // resize to 4 by 3
    printMatrix(mstr);
    cout << "Resize to 2 by 2:" << endl;
    mstr.resize(2, 2); // resize to 2 by 2
    printMatrix(mstr);
    */

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
    while (getline(TestFile, currentline)) //while ( getline(TestFile, Buffer) )
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
        cout << *db;
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
  else // cout << "Unable to open file"; 
  cout << "Unable to open input file " << INPUT_FILE << endl;  

  // delete the database of variables
  delete db;  

  //cout << "Press any key to end...";
  //cin.get();  // wait for a key to end your program

  return 0;  
}

////////////////////////////////////////////////////////////////////////////////
// functions related to the command line interpreter

// We only allow:
// type asn:   e.g., a = b              (iSeg = 3)
// type unary: e.g., a++                (iSeg = 2)
// type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)

// bool Partitioner(string& Input)
//int Partitioner(char* Buffer,  int segmt[][2], int& iSeg)
/*void Interpreter(string& Input)
{
  char Buffer[500]; // array buffer to hold the command line
  strncpy(Buffer, Input.c_str(), sizeof(Buffer));
  Buffer[sizeof(Buffer) - 1] = 0;

  /*
  // indicator LAB 3
  int st=0; // start point
  int ed=0; // end point
  */
  /*
  bool Tag = false;
  // int error_code = 1;    // LAB 3
  // bool error_code = true;  // LAB 2

  int iSeg = 0; // number of segments in command line

  int segmt[10][2]; // record the location of each segment
  // LAB 2 // the location of each segment: start point, length

  OP  op; // the operator in the command line

  // result_name, operand_1 and operand_2
  char res[50], operand_1[50], operand_2[50]; 


  // // if the command line can be successfully segment
  // if(Partitioner(Buffer,segmt,iSeg))

  // ------------------------------------------------------
  // begin partitioner incorporation ------------------

  // indicator
  int st=0; // start point
  int ed=0; // end point
  int error_code = 1; 
  
  // get the length of command line
  int len = (int)strlen(Buffer);

  while(st<len)
  {
    while(Buffer[st]==' '&&st<len)st++;

    ed = st;

    if(st==len) // if(st==len) // lab 2
    {
      if (iSeg==0)
      {
        error_code = 0; // error_code = false; // lab 2
        // break; // lab2
      }       
      break; // not in lab 2
    }
    else
    {
      // check consecutive characters
      if(IsAChar(Buffer[st])) 
      {
        while((ed<len)&&(IsAChar(Buffer[ed])||IsADigit(Buffer[ed])||Buffer[ed]=='_'))ed++;
      }

      // check consecutive digits
      else if(IsADigit(Buffer[st])) 
      {
        while((ed<len)&&(IsADigit(Buffer[ed])||Buffer[ed]=='.'))ed++;
      }

      // check consecutive operators
      else if(IsAOperator(Buffer[st])) 
      {
        while((ed<len)&&(IsAOperator(Buffer[ed])))ed++;
      }

      // check matrix
      else if((Buffer[st]=='['))  
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
            cout<<"Expect a ']' here."<<endl;
            error_code = 0;
            // error_code = false; // lab 2
            break;
          }
          ed++;
        }
      }
      else if(Buffer[st]==';')ed++;
      else
      {
        error_code = 0;
      }

    }
    if(error_code)
    {
      segmt[iSeg][0] = st;
      segmt[iSeg][1] = ed-st;
      iSeg = iSeg++; // iSeg = iSeg+1; // lab 2
      st = ed;
    }  
    else
    {
      // return error_code; // lab 2
      break;
    }  
  } 

  /*
  // lab 2
  // print each segment
  for (int i =0; i<iSeg; i++)
  {
    for (int j=0; j<segmt[i][1]; j++)
    {
      cout<<Buffer[segmt[i][0]+j];
            
    }
    cout<<endl;
  }
    */

  //return error_code; lab 2 and 3

/*
  // if the command line can be successfully segment
  //if(Partitioner(Buffer,segmt,iSeg))
  if(error_code == 1)
  {
    // valid cases can be : 2, 3 or 5
    switch (iSeg) 
    {
      // the command line is possible to be unary operation
    case 2: 
      {
        // if it is a valid unary operation
        Tag = IsAUnary(Buffer,segmt,operand_1,op); 
        if(Tag)
        {   // it is a valid unary operation, output the result
          OpTranslator(op); 
          cout<<" "<<operand_1<<endl;
        }  
        break;      
      }
      // the command line is possible to be binary operation or assignment
    case 3: 
      {
        if(IsAAsn(Buffer,segmt,res,operand_1)) // if it is a valid assignment
        {   // it is a valid assignment, output the result
          Tag = true;
          cout<<"ASN "<<" "<<operand_1<<" to "<< res <<endl;
        }
        else if(IsABinary3(Buffer,segmt,operand_1,operand_2,op)) // if it is a binary operation with assignment to default variable ans
        {   // it is a binary operation, output the result
          Tag = true;
          OpTranslator(op);
          cout<<" "<<operand_1<<" AND "<<operand_2<<" , THEN ASN to ans. "<<endl;
        }
        break;
      }
      // the command line is possible to be binary operation and assignment
    case 5: 
      {
        Tag = IsABinary5(Buffer,segmt,res,operand_1,operand_2,op); // if it is a binary operation with assignment to a specified variable
        if(Tag)
        {   // it is a binary operation, output the result
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

}*/


//void Interpreter(string& Input)
//int Partitioner(char* Buffer,  int segmt[][2], int& iSeg)
/* ----------------------------------------------------------------------------
 Name:     interpreter
 Purpose:  
 Params:   
 Returns:  
 ----------------------------------------------------------------------------*/ 
 void interpreter(const char* cmd)
 {
  /* // lab 3 or 2+3
  char Buffer[500]; // array buffer to hold the command line
  strncpy(Buffer, Input.c_str(), sizeof(Buffer));
  Buffer[sizeof(Buffer) - 1] = 0;
  */

  /*
  // indicator LAB 3
  int st=0; // start point
  int ed=0; // end point
  */


   //char buffer[500];
  segment_t* segmt;


   // int segmt[10][2]; // record the location of each segment // lab 3
  // LAB 2 // the location of each segment: start point, length

   // lab 3
   // result_name, operand_1 and operand_2
   //char res[50], operand_1[50], operand_2[50]; 
  char* lhs;
  char* left;
  char* right;

   //  OP  op; // the operator in the command line
  op_t op;

   //int iSeg = 0; // number of segments in command line
   // type asn:   e.g., a = b              (iSeg = 3)
   // type unary: e.g., a++                (iSeg = 2)
   // type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)
  int numSeg;

   // aka error_code = 1 or true or Tag or isValid = false
  bool success; 



   // // if the command line can be successfully segment
  // if(Partitioner(Buffer,segmt,iSeg))

   //*****************************************************//
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
    //cout << "case 3 " << segmt[2].type; tryign to fiure out how to display matrix
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
/*if (Tag == false) // if the command line is not valid
  {
    cout<<"Sorry, do not understand." <<endl;
  }*/
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
  //int pos, len, bpos, count; // pos numseg st and ed
  //int pos, bpos, count;
  int count;
  char* buffer;
  char c; // current character
  int bpos;

  int pos = 0;
  numseg = 0;
  //First loop:  input checking and segment counting
  //pos = numseg = 0;
  // indicator
  //int st=0; // start point
  //int ed=0; // end point
  // int error_code = 1;  lab 2 i thik or 3
  // ------------------------------------------------------
  // begin partitioner incorporation ------------------


  // get the length of command line
  int len = strlen(cmd); // int len = (int)strlen(Buffer);
  while (pos < len) // while(st<len)
  {
    // while(Buffer[st] ==' ' && st<len) st++;
    // ed = st; // lab 23 did it at beginning,
    // this one increments after getting current char
    c = cmd[pos]; // the current character at this position


    // Variable name

    // check consecutive characters
    if (isChar(c))  // if(IsAChar(Buffer[st])) 
    {
      pos++;
      // Oh WOW this is to enforce the convention/limitation/whatever
      // that variables can't start with a number
      // Characters after the first are allowed to be 0-9... at least i think
      while (pos < len && (isChar(cmd[pos]) || (cmd[pos] >= '0' && cmd[pos] <= '9')))
        pos++;
      // while( (ed<len)&&(IsAChar(Buffer[ed]) || IsADigit(Buffer[ed]) || Buffer[ed]=='_')) ed++;
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
      pos++;
      while (pos < len && cmd[pos] != ']') pos++;
      /*char *matrixdata = new char[500]; // = '[';
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
  */
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
  else return c == '_'; // still don't understand why returns a char not bool?
}
// lab 2+3
/*
bool IsAChar(char str) {
  bool Tag = false;
  if((str>='A'&&str<='Z')||(str>='a'&&str<='z')) Tag = true;
  return Tag;
}*/

/* ----------------------------------------------------------------------------
 Name:     isDigit
 Returns:  
 ---------------------------------------------------------------------------- */
 bool isDigit(char c)
 {
  if (c >= '0' && c <= '9') return true;
  else return c == '.'; // still don't understand why returns a char not bool?
  // oh wow i get it this will return true if its a decimal (ie still part of a number)
  // and otherwise false
  // that is SO NOT OBVIOUS
}
// lab 2+3
/*bool IsADigit(char str) {
  bool Tag = false;
  if((str>='0'&&str<='9')||(str=='.')) Tag = true;
  return Tag;
}*/

/* ----------------------------------------------------------------------------
 Name:     isOperator
 Returns:  
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
// lab 2+3
/*bool IsAOperator(char str) {
  bool Tag = false;
  if((str=='+')||(str=='-')||(str=='*')||(str=='/')||(str=='=')) Tag = true;
  return Tag;
}*/

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