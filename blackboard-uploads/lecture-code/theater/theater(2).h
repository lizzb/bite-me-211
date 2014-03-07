/**
 Example class to represent seating in a theater with an 8 x 8 grid of seats
 See theater.cpp for a description of all functions

 @author William Hendrix
 */

#ifndef __THEATER_H
#define __THEATER_H

#include <iostream>
using namespace std;

#define NROW 8
#define NCOL 8

class Theater
{
  friend ostream& operator<<(ostream& out, Theater& t);
private:
  char seats[NROW];
public:
  Theater();
  bool isReserved(int row, int col) const;
  bool reserve(int row, int col);
  bool cancelReservation(int row, int col);
};

ostream& operator<<(ostream& out, Theater& t);

#endif
