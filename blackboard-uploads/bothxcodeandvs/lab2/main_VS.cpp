/**
  Add descriptive comment here
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX_BUFFER_SIZE 500

// Check if the input is a letter ('a'~'z', 'A'~'Z')
bool isAChar(char); 
// Check if the input belongs in a number ('1'~'9' or a decimal point '.')
bool isADigit(char);
// Check if the input is a valid operator (+ , - , * , ++, -- are valid)
bool isAnOperator(char); 
// Function to process the command line
bool partitioner(string&); 

//Do not edit main() except to add your name
int main()
{
	//Print welcome message
	cout << endl;
	cout << "\tWelcome to EECS 211 Lab 2:  a command line partitioner" << endl;
	cout << "\t\tName "<< endl; // your name here 
	cout << "\t\t   Copyright, 2014   " << endl; 

	//Get the input
	string buffer;
	int numCmds = 0;
	ifstream testFile("TestCases.txt"); // read from file

	if (testFile.is_open()) // open file
	{
		while (getline(testFile, buffer)) // read a command
		{
			if (buffer.compare("quit") == 0) // if the input is 'quit'
			{
				cout<<"\nThank you, goodbye. "; //quit the program
				break;
      }
			else
			{
				// Process the command line
				cout << "\n#" << ++numCmds << " : " << buffer << endl; // Print the command line

				// Function patitioner(buffer) parses the input and returns whether or not the input is valid
				if (!partitioner(buffer)) 
					cout << "That is an invalid command." << endl;
			}
		}
		testFile.close();
	}
	else 
		cout << "Unable to open test file\n"; 

	cout<<"Press any key to exit..."<<endl;
	getchar(); 
	
	return 0;       
}

/**
  Add descriptive comment here
*/
bool partitioner(string& input)
{
	char buffer[MAX_BUFFER_SIZE];
	strncpy(buffer, input.c_str(), sizeof(buffer));
	buffer[sizeof(buffer) - 1] = '\0';

	// Add code here to parse the characters in buffer and print the tokens
	cout << "Parsing command tokens\n";
	
	//Return whether or not the characters formed a valid command
	return true;
}

/**
  Add a descriptive comment here
 */
bool isAChar(char test) 
{
	return true;
}

/**
  Add a descriptive comment here
 */
bool isADigit(char test) 
{
	return true;
}

/**
  Add a descriptive comment here
 */
bool isAnOperator(char test) 
{
	return true;
}