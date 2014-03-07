//
//  main.cpp
//  Patitioner
//
//  Created by Nan Jiang on 1/20/14.
//  Copyright (c) 2014 Nan Jiang. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool IsAChar(char); // check if the input is a character or not ('a'~'z', 'A'~'Z')

bool IsADigit(char); // check if the input is a digit or not ('1'~'9' or the dot '.' in decimal, like 3.14)

bool IsAOperator(char); // check if the input is a operator or not (+ , - , * , \, ++, --)

bool Partitioner(string&); // function to process the command line


int main(int argc, const char * argv[])
{
	// print welcome message
	cout << endl;
	cout << "\tWelcome to the EECS 211 MP#2: A Command Line Partitioner" << endl;
	cout << "\t\t     Your Name "<< endl; // your name here
	cout << "\t\t   Copyright, 2014   " << endl;
    
	//Get the input
	string Buffer;
    
	int num_Case=0;

	ifstream TestFile("TestCases.txt"); // read from file
    
	if (TestFile.is_open())// open file
	{
		while ( getline(TestFile,Buffer) )// read a command line
		{
			if (Buffer.compare("quit")==0) // if the input is 'quit'
			{
				cout<<"\nThank you. "; //quit the program
			}
			else
			{
				// process the command line
				cout<<"\n# "<<++num_Case <<" : "<<Buffer<<endl; // print the command line
				
				// function Patitioner(Buffer) returns 1 when the parsing is completed. And the segments are printed on screen.
				// function Patitioner(Buffer) returns 0 when the input command line is not valid.
				if (Partitioner(Buffer)==0)
				{
					cout<<"Sorry, do not understand."<<endl;
				}
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



bool Partitioner(string& Input)
{
	char Buffer[500];
	strncpy(Buffer, Input.c_str(), sizeof(Buffer));
	Buffer[sizeof(Buffer) - 1] = 0;
    
	// indicator
	int st=0; // start point
	int ed=0; // end point
	bool error_code = true;
	int iSeg=0; // number of segments in command line
	int segmt[10][2]; // the location of each segment: start point, length
    
	// get the length of command line
	int len = (int)strlen(Buffer);
    
    
	while(st<len)
	{
		while(Buffer[st]==' '&&st<len)st++;
        
		ed = st;
        
		if(st==len)
		{
			error_code = false;
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
			else if(Buffer[st]=='[') // check matrix
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
						error_code = false;
						break;
					}
					ed++;
				}
			}
			else if(Buffer[st]==';')ed++;
			else
			{
				error_code = false;
			}
            
		}
		if(error_code)
		{
			segmt[iSeg][0] = st;
			segmt[iSeg][1] = ed-st;
			iSeg = iSeg+1;
			st = ed;
		}
		else
		{
			return error_code;
		}
	}
    
	// print each segment
	for (int i =0; i<iSeg; i++)
	{
		for (int j=0; j<segmt[i][1]; j++)
		{
			cout<<Buffer[segmt[i][0]+j];
            
		}
		cout<<endl;
	}
    
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


