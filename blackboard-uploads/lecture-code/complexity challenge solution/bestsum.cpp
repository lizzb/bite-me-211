/**
 Sample solution for "best sum" problem
 The challenge was to develop a linear-time algorithm to find the two values in
 an array whose sum is as close as possible to a target value, without going over
 This solution reads in the array from the file "array.txt" and accepts targets
 via cin.
 This file also contains unused functions for generating a random sorted array
 of 1000 elements, as well as a sample solution for BestSum that takes quadratic time

 @author William Hendrix
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

#define ARRAY_FILE "array.txt"
#define NUM_TEST_ELEMENTS 1000

void bestsum(int* arr, int len, int target, int& left, int& right);
void printArray(int* arr, int len);
int* readArray(const char* filename, int& len);
void generateTestArray();

/**
 Given a sorted array of integers, finds the two indices such that their sum is
 as close as possible, without exceeding, a given target
 The two indices need not be distinct, though the code could be easily modified
 to force them to be distinct
 Returns (-1, -1) if there is no sum that does not exceed the target
 Does not check if array is sorted (may return incorrect result if not sorted)
 Runs in linear time w.r.t. array size (single-pass algorithm)

 How it works:
 The algorithm keeps two pointers in the array, left and right.  Throughout the
 algorithm, we move the right pointer leftwards when the current sum is too
 large and the left pointer rightwards when it can be increased.  When the left
 pointer stops, the sum has reached a "local max," and we compare it to our
 best sum so far.  
 
 The reason this works is that for every element in the array <= target / 2, 
 there is an element that gets as close as possible to target without going
 over, and as we move rightward through the array, that "optimal" element can
 only move to the left.  Thus, we don't need to compute every sum, just
 continue to scan for the next "optimal" element from the last one.  We update
 the max as needed, then advance to the next element and continue scanning.
 
 The algorithm stops when the "current" element (left) and the "optimal"
 element (right) pass each other.  (Since addition is symmetric, we can just
 find the pair where left <= right.)  Since we never scan "backwards," each
 element will be passed by left and right at most once, for a runtime of O(n).

 @param arr the array to scan
 @param len the number of integers in the array
 @param target the target value
 @param best1 (output parameter) the first index of the pair
 @param best2 (output parameter) the second index of the pair
 */
void bestsum(int* arr, int len, int target, int& best1, int& best2)
{
  int left, right, temptarget, best;
  
  //Start with left and right "hands" at the ends of the array
  left = 0;
  right = len - 1;
  
  //Move "right hand" leftward until arr[left] + arr[right] <= target
  temptarget = target - arr[left];
  while (left <= right && arr[right] > temptarget)
    right--;
  //If no such numbers exist, return (-1, -1)
  if (right < 0)
  {
    best1 = best2 = -1;
    return;
  }
  best = arr[left] + arr[right];
  best1 = left;
  best2 = right;

  do
  {
    //Move "left hand" until arr[left] + arr[right] > target
    temptarget = target - arr[right];
    while (left <= right && arr[left] <= temptarget)
      left++;

    //Check if last value we passed beats our current best
    if (best < arr[left - 1] + arr[right])
    {
      best = arr[left - 1] + arr[right];
      best1 = left - 1;
      best2 = right;
    }

    //Early termination if "hands" have crossed
    if (left >= right)
      break;

    //Move "right hand" until arr[right] + arr[right] <= target
    temptarget = target - arr[left];
    while (left <= right && arr[right] > temptarget)
      right--;
  } while (left < right);
}

/**
 Example solution for solving the problem in O(n^2) time
 Calculates every sum and finds that max that doesn't exceed the target

 @param arr the array to scan
 @param len the number of integers in the array
 @param target the target value
 @param best1 (output parameter) the first index of the pair
 @param best2 (output parameter) the second index of the pair
 */
void slowsum(int* arr, int len, int target, int& best1, int& best2)
{
  int best, sum;
  best1 = best2 = -1;

  best = arr[0] * 2 - 1;
  for (int i = 0; i < len; i++)
    for (int j = i; j < len; j++)
    {
      sum = arr[i] + arr[j];
      if (sum > best && sum <= target)
      {
        best1 = i;
        best2 = j;
        best = sum;
      }
    }
}

int main()
{
  int* arr;
  int len, l, r, tgt;
  char c;

  //Read in the array from file
  arr = readArray(ARRAY_FILE, len);
  if (arr == NULL)
  {
    cout << "Error opening file" << ARRAY_FILE << endl;
    cout << "Type 'q' to quit: ";
    cin >> c;
    return 0;
  }

  do
  {
    /*
    cout << "Array: ";
    printArray(arr, len);
    cout << endl;
    //*/

    //Get the target value
    do
    {
      cout << "Enter target: ";
      cin.clear();
      cin >> tgt;
      cin.sync();
    } while (cin.fail());

    //Find the best sum
    bestsum(arr, len, tgt, l, r);

    //Output the sum
    if (l < 0 || r < 0)
      cout << "No sum is less than that target\n";
    else
      cout << "Best sum:  " << arr[l] << " + " << arr[r] << " = " << arr[l] + arr[r] << endl;

    cout << "Type 'r' to retry, or anything else to quit: ";
    cin >> c;
    } while (c == 'r');
  
  //Clean up and exit
  delete arr;
  return 0;
}

/**
 Utility function to print out an array of integers

 @param arr the array to print
 @param len the number of integers in the array
 */
void printArray(int* arr, int len)
{
  if (len > 0)
    cout << arr[0];
  for (int i = 1; i < len; i++)
    cout << ' ' << arr[i];
}

/**
 Utility function to read in an array of integers from a file
 Reads file until first non-integer (or end-of-file)

 @param filename the name of the file to read
 @param len (output parameter) the number of integers read from the file

 @return the allocated array (calling function must free)
 */
int* readArray(const char* filename, int& len)
{
  int temp;
  int* ret;
  ifstream in(filename);

  if (!in.is_open())
    return NULL;

  //Count # of elements in array
  len = 0;
  while (in >> temp)
    len++;

  //Rewind the file stream
  in.clear();
  in.seekg(0L);
  
  //Allocate the array and read in the elements
  ret = new int[len];
  for (int i = 0; i < len; i++)
    in >> ret[i];

  in.close();
  return ret;
}

/**
 Utility function to generate a random sorted array with NUM_TEST_ELEMENTS elements
 Numbers will be in the range (-RAND_MAX / 2, RAND_MAX / 2)
 Resultant array will almost certainly contain duplicates with 1000 elements

 Array will be output to the file ARRAY_FILE
 */
void generateTestArray()
{
  ofstream out(ARRAY_FILE);
  vector<int> arr;

  srand(time(0));
  for (int i = 0; i < NUM_TEST_ELEMENTS; i++)
    arr.push_back(rand() - RAND_MAX / 2);
  sort(arr.begin(), arr.end());

  for (int i = 0; i < NUM_TEST_ELEMENTS; i++)
    out << arr[i] << '\n';

  out.close();
}
