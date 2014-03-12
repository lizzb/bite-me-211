//
// EECS 211 MP#2: A Command Line Interpretation
// Nan Jiang, Northwestern University
// Copyright, 2014
//
// This project is to  Resolve a command line by checking the grammar of the command
// and explain the command line

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC}; // enumeration of operator types

//function declaration
void Interpreter(string&); 
bool IsAUnary(char*, int [][2], char*, OP&); // if the command line is valid unary operation
bool IsAAsn(char*, int [][2], char*, char*); // if it is a valid assignment
bool IsABinary3(char*, int [][2], char*, char*, OP&); // if it is a valid binary operation
bool IsABinary5(char*, int [][2], char*, char*, char*, OP&);// if it is a valid assignment and binary operation
void OpTranslator(OP); // output the operator


// functions from the previous project
int Partitioner(char*, int [][2], int&); // partitioning the command line into segments
bool IsAChar(char); // if input is a letter
bool IsADigit(char); // if it is a digit
bool IsAOperator(char); // if it is an operator


void main()
{
	// print welcome message
	cout << endl;
	cout << "\tWelcome to the EECS 211 MP#3: A Command Line Interpreter" << endl;
	cout << "\t\tNan Jiang, Northwestern University "<< endl;
	cout << "\t\t   Copyright, 2014   " << endl;   

	//Get the input
	string Buffer;

	int num_Case=0;

	ifstream TestFile("TestCase.txt"); // read from file

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
				Interpreter(Buffer); // not in lab 2
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
// function Patitioner(Buffer) returns 1 when the parsing is completed.
// And the segments are printed on screen.
				// function Patitioner(Buffer) returns 0 when the input command line is not valid.
				
////////////////////////////////////////////////////////////////////////////////
// functions related to the command line interpreter

// We only allow:
// type asn:   e.g., a = b              (iSeg = 3)
// type unary: e.g., a++                (iSeg = 2)
// type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)

// bool Partitioner(string& Input)
//int Partitioner(char* Buffer,  int segmt[][2], int& iSeg)
void Interpreter(string& Input)
{
	char Buffer[500]; // array buffer to hold the command line
	strncpy(Buffer, Input.c_str(), sizeof(Buffer));
	Buffer[sizeof(Buffer) - 1] = 0;

	/*
	// indicator LAB 3
	int st=0; // start point
	int ed=0; // end point
	*/
	
	bool Tag = false;
	// int error_code = 1; 		// LAB 3
	// bool error_code = true; 	// LAB 2

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

}

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
}

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
}

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
}

// explain operators
void OpTranslator(OP op) 
{
	switch(op){
	case ASN:
		cout << "ASN" ;
		break;
	case ADD:
		cout << "ADD" ;
		break;
	case MIN:
		cout << "MIN" ;
		break;
	case MUL:
		cout << "MUL" ;
		break;
	case DIV:
		cout << "DIV" ;
		break;
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
// bool Partitioner(string& Input)
int Partitioner(char* Buffer,  int segmt[][2], int& iSeg)
{
	/* 
	char Buffer[500];
	strncpy(Buffer, Input.c_str(), sizeof(Buffer));
	Buffer[sizeof(Buffer) - 1] = 0;
	*/


	// indicator
	int st=0; // start point
	int ed=0; // end point
	int error_code = 1; 

	/*
	bool error_code = true;
	int iSeg=0; // number of segments in command line
	int segmt[10][2]; // the location of each segment: start point, length
    */

	// get the length of command line
	int len = (int)strlen(Buffer);


	while(st<len)
	{
		while(Buffer[st]==' '&&st<len)st++;

		ed = st;


		/*
		if(st==len)
		{
			error_code = false;
			break;
		}
		*/

		if(st==len)
		{
			if (iSeg==0)
			{
				error_code = 0;
			} 			
			break;
		}
		else
		{
			if(IsAChar(Buffer[st])) // check consecutive characters
			{
				while((ed<len)&&(IsAChar(Buffer[ed])||IsADigit(Buffer[ed])||Buffer[ed]=='_'))ed++;
			}
			else if(IsADigit(Buffer[st])) // check consecutive digits
			{
				while((ed<len)&&(IsADigit(Buffer[ed])||Buffer[ed]=='.'))ed++;
			}
			else if(IsAOperator(Buffer[st])) // check consecutive operators
			{
				while((ed<len)&&(IsAOperator(Buffer[ed])))ed++;
			}
			else if((Buffer[st]=='['))  // check matrix
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
						// error_code = false;
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
			iSeg = iSeg++; // iSeg = iSeg+1;
			st = ed;
		}  
		else
		{
			// return error_code;
			break;
		}  
	} 
	/*

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

	return error_code;
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

