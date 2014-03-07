#include <iostream>
using namespace std;

int findMax(int num1, int num2);

int main()
{
  cout << "findMax(-3, 1000) = " << findMax(-3, 1000) << endl;
  cout << "findMax(1000, 1001) = " << findMax(1000, 1001) << endl;
  cout << "findMax(1000, 1000) = " << findMax(1000, 1000) << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}

/**
 Function for finding maximum of two integers

 @param num1 first integer
 @param num2 second integer
 @return the maximum of num1 and num2

 @author EECS 211, Winter 2014
 */
int findMax(int num1, int num2)
{
  if (num1 > num2)
    return num1;
  else
   return num2;
}