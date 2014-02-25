// from http://pastebin.com/1sB0CG8c

//
// EECS 211 MP#2: A Command Line Interpretation
// Nan Jiang, Northwestern University
// Copyright, 2014
//
// This project is to  Resolve a command line by checking the grammar of the command
// and explain the command line

// #include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// enumeration of operator types - aka "enums"
// enums allow you to refer to numbers with a more meaningful label
// for better code readability
enum OP {ASN, ADD, MIN, MUL, DIV, PRE_INC, PRE_DEC,POST_INC,POST_DEC};




int main()
{
	// print welcome message
	cout << endl;
	cout << "\tWelcome to the EECS 211 MP#3: A Command Line Interpreter" << endl;
	cout << "\t\tNan Jiang, Northwestern University "<< endl;
	cout << "\t\t   Copyright, 2014   " << endl;   

	// Get the input
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

	int segmt[10][2]; // record the location of each segment

	int iSeg = 0; // number of segments in command line

	bool Tag = false;

	OP  op; // the operator in the command line

	char res[50], operand_1[50], operand_2[50]; // result_name, operand_1 and operand_2

	if(Partitioner(Buffer,segmt,iSeg))// if the command line can be successfully segment
	{

		switch (iSeg) // valid cases can be : 2, 3 or 5
		{
		case 2: // the command line is possible to be unary operation
			{
				Tag = IsAUnary(Buffer,segmt,operand_1,op); // if it is a valid unary operation
				if(Tag)
				{   // it is a valid unary operation, output the result
					OpTranslator(op); 
					cout<<" "<<operand_1<<endl;
				}  
				break;      
			}
		case 3: // the command line is possible to be binary operation or assignment
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
		case 5: // the command line is possible to be binary operation and assignment
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
