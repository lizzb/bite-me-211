#include <iostream>
using namespace std;

//Program to reduce a number to its prime factors
int main()
{
  int number, test;
  
  cout << "Please input a number to factor: ";
  cin >> number;
  
  if (cin.fail())
  {
    cout << "That is not a number; type 'q' to quit: ";
    char c;
    cin >> c;
    return 1;
  }
  if (number < 2)
  {
    cout << "That number is too small to factor.  Type 'q' to quit: ";
    char c;
    cin >> c;
    return 2;
  }
  
  cout << endl << number << " = ";
  test = 2;
  while (test * test <= number)
  {
    if (number % test == 0)
    {
      cout << test << '*';
      number = number / test;
    }
    else if (test == 2)
      test = 3;
    else //Only check odd divisors after 2
      test += 2;
  }
  cout << number << endl;
  
  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;

  return 0;
}
