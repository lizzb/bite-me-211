/**
 Driver program to test Theater class defined in theater.h and theater.cpp

 @author William Hendrix
 */

#include <iostream>
#include "theater.h"
using namespace std;

int main()
{
  Theater sundayShowing;

  cout << "Theater before tickets go on sale:\n" << sundayShowing << endl;

  //Reserve front row
  for (int i = 0; i < NCOL; i++)
    if (sundayShowing.reserve(0, i))
      cout << "Invalid reservation (" << 0 << ", " << i << ")\n";
    else
      cout << "(" << 0 << ", " << i << ") reserved\n";

  //Reserve seats in a checkerboard pattern
  for (int i = 0; i < NROW; i++)
    for (int j = i & 1; j < NCOL; j += 2)
      if (sundayShowing.reserve(i, j))
        cout << "Invalid reservation (" << i << ", " << j << ")\n";
      else
        cout << "(" << i << ", " << j << ") reserved\n";

  cout << "Middle of the week:\n" << sundayShowing << endl;

  //Cancel all reservations in the back row (some invalid)
  for (int i = 0 ; i < NCOL; i++)
    if (sundayShowing.cancelReservation(NROW - 1, i))
      cout << "Invalid cancellation (" << NROW - 1 << ", " << i << ")\n";
    else
      cout << "(" << NROW - 1 << ", " << i << ") cancelled\n";

  //Cancel a few other reservations
  for (int i = 0; i < NROW; i++)
    if (sundayShowing.cancelReservation(i, (5 * i) % NROW))
      cout << "Invalid cancellation (" << i << ", " << (5*i)%NROW << ")\n";
    else
      cout << "(" << i << ", " << (5*i)%NROW << ") cancelled\n";

  cout << "After cancellations:\n" << sundayShowing << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}