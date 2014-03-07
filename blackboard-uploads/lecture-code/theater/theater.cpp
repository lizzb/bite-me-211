/**
 Example class to describe and reserve seats in an 8 x 8 theater
 Demonstrates the use of bitwise operations to "pack" 8 binary (bool) values
 into a single char

 @author William Hendrix
 */

#include <string.h>
#include "theater.h" //includes <iostream>

/**
 Default constructor
 Initializes an empty Theater
 */
Theater::Theater()
{
  memset(seats, 0, NROW);
}

/**
 Tests whether seat (row, col) is reserved
 Value that are out of bounds will return false

 @param row row number of the seat to test (0 base)
 @param col column number of the seat to test (0 base)

 @return whether the seat is reserved
 */
bool Theater::isReserved(int row, int col) const
{
  if (row < 0 || row > NROW || col < 0 || col > NCOL)
    return false;

  //seats[x] represents the 8 sets in row x
  //1 << x is an int with only bit x set
  if (seats[row] & (1 << col)) //nonzero if bit col in seats[row] is set
    return true;
  else
    return false;
}

/**
 Reserves seat (i, j) in the theater
 Returns true if indices are out of bounds or the seat is already reserved

 @param row row number of the seat to reserve
 @param col column number of the seat to reserve

 @return whether an error occurred while reserving the seat
 */
bool Theater::reserve(int row, int col)
{
  if (row < 0 || row > NROW || col < 0 || col > NCOL || isReserved(row, col))
    return true;

  //Set col bit in seats[row]
  seats[row] |= 1 << col;
  return false;
}

/**
 Cancels the reservation for seat (i, j)
 Returns true if indices are out of bounds or the seat is not reserved

 @param row row number of the reservation to cancel
 @param col column number of the reservation to cancel

 @return whether an error occurred while cancelling the reservation
 */
bool Theater::cancelReservation(int row, int col)
{
  if (row < 0 || row > NROW || col < 0 || col > NCOL || !isReserved(row, col))
    return true;

  //~(1 << col) has every bit but col set
  //Unsets bit col in seats[row]
  seats[row] &= ~(1 << col);
  return false;
}

/**
 Prints the Theater occupancy
 */
ostream& operator<<(ostream& out, Theater& t)
{
  out << "  01234567\n";
  for (int i = NROW - 1; i >= 0; i--)
  {
    out << i << ' ';
    for (char test = 1; test != 0; test <<= 1) //When does 1 << n == 0?
      if (t.seats[i] & test)
        out << '*';
      else
        out << '-';
    out << '\n';
  }
  out << "  (front)\n";
  return out;
}