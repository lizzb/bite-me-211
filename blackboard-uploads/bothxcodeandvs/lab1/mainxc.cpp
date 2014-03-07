#include <fstream>
#include <iostream>
using namespace std;

/**
 Utility function for reading in four values from an input stream that describe a sequence.
 The first, second, and fourth inputs should be integers, while the third should be a character.
 Returns true if all input types match and no other I/O error occurs, otherwise returns false.
 May read fewer than four values if an error occurs.

 @param min  [output argument] The minimum value for the sequence (the next value in the stream)
 @param max  [output argument] The maximum value for the sequence (the second value in the stream)
 @param type [output argument] The type of the sequence (the third value in the stream)
 @param opt  [output argument] The delta or number of elements for the sequence (the fourth value)
 @param in   The input stream (cin or ifstream) from which values are read
 
 @return Returns true if no errors occurred during input

 @author William Hendrix, 2014
 */
bool getValidSequence(int& min, int& max, char& type, int& opt, istream& in)
{
  return in >> min >> max >> type >> opt;
}

/** 
  Descriptive comment goes here

  @author Me, Year
 */
int main()
{
  //Variable declarations
  int min, max, option;
  char type;
  ifstream file("p1input.txt");

  //Add your variable declarations here

  //Modify and extend the following code to match the lab specifications
  bool valid = getValidSequence(min, max, type, option, file);
  if (valid)
    cout << "That is sequence " << min << ':' << max << ", with " << type << " = " << option << endl;
  else
    cout << "That is an invalid sequence\n";

  char c;
  cin >> c;
  return 0;
}