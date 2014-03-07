#include <fstream>
#include <iostream>
using namespace std;

#define EPSILON 1e-13

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
  in >> min >> max >> type >> opt;
  return !in.fail;
}

/** 
  Descriptive comment goes here

  @author Me, Year
 */
int main()
{
  int min, max, count;
  char type;
  double option, delta;

  ifstream file("p1input.txt");

  while (getValidSequence(min, max, type, option, file))
  {
    //cout << "That is sequence " << min << ":" << max << ", with " << type << " = " << option << endl;

    if (min > max)
    {
      cout << "Invalid max and min values\n";
      continue;
    }

    if (type == 'd')
    {
      if (option <= 0)
      {
        cout << "Invalid value for delta\n";
        continue;
      }
      delta = static_cast<double>(option);
      count = static_cast<int>((max - min) / delta + EPSILON);
    }
    else if (type == 'n')
    {
      count = static_cast<int>(option) - 1;
      if (count < 0 || count == 0 && max > min)
      {
        cout << "Invalid number of elements\n";
        continue;
      }
      delta = static_cast<double>(max - min) / (option - 1);
    }
    else
    {
      cout << "Invalid sequence type\n";
      continue;
    }

    cout << min;
    for (int j = 1; j <= count; j++)
      cout << " " << min + j * delta;
    cout << endl;
  }
  
  char c;
  cin >> c;
  return 0;
}
