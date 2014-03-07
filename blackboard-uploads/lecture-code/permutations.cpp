/**
 Example program that prints all permutations of the numbers 1-n for n up to 8
 
 @author William Hendrix
 */
#include <iostream>
using namespace std;

void print(int arr[], int len);
void allperm(int arr[], int len);
void perm(int arr[], int len, int frozen);

int main()
{
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int n = 0;
  
  do
  {
    cout << "Enter a number between 1 and 8: ";
    cin >> n;
    cin.ignore(1000, '\n');
    cin.clear();
  } while (n < 1 || n > 8);

  cout << "The permutations of 1-" << n << " are as follows:\n";
  allperm(arr, n);
  
  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;

  return 0;
}

/**
 Utility function to print values in an array

 @param arr the array to print
 @param len the size of the array
 */
void print(int arr[], int len)
{
  for (int i = 0; i < len; i++)
    cout << arr[i] << ' ';
  cout << endl;
}

/**
 Function that recursively prints all permutations of values in an array

 @param arr array of values to permute
 @param len the size of the array
 */
void allperm(int arr[], int len)
{
  perm(arr, len, 0);
}

/*
 Recursive function for printing permutations
 Not intended to be called directly
 */
void perm(int arr[], int len, int frozen)
{
  if (frozen >= len)
  {
    print(arr, len);
    return;
  }

  for (int i = frozen; i < len; i++)
  {
    int t = arr[i];
    arr[i] = arr[frozen];
    arr[frozen] = t;
    perm(arr, len, frozen + 1);
    arr[frozen] = arr[i];
    arr[i] = t;
  }
}
