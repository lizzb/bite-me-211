#include <iostream>
using namespace std;

/**
  Example program for calculating the average of a set of grades
  
  @author William Hendrix
 */
int main()
{
  int value, count, sum;
  double average;
  char letter;
  
  //Initialize the sum and the count to 0
  sum = 0;
  count = 0;
  
  //Prompt the user for a number
  cout << "Enter a grade: ";
  cin >> value;

  //While the user enters valid numbers, add it to the sum, increment the count, and prompt again
  while (!cin.fail())
  {
    sum = sum + value;
    count = count + 1;
    cout << "Enter another grade, or type 'quit' to stop: ";
    cin >> value;
  }

  //Calculate and display the average
  average = static_cast<double>(sum) / count;
  cout << "The average of the grades you entered is " << average << endl;
  
  //Calculate a letter grade:  assume 10-point scale
  if (average < 60)
    letter = 'F';
  else if (average < 70)
    letter = 'D';
  else if (average < 80)
    letter = 'C';
  else if (average < 90)
    letter = 'B';
  else
    letter = 'A';

  cout << "This grade represents a(n) ";
  cout << letter;
  cout << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin.clear();
  cin.sync();
  cin >> c;
  return 0;
}
