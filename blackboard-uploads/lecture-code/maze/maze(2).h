/**
 Definition file for Maze class, direction enumerated type, and coordinate struct.
 Mazes store a rectangular grid of characters to represent a maze.  
 Walls are represented by '#', the entrance and exit by 'S' and 'E', and hallways are ' '.  
 The Maze also keeps track of a walker that can navigate through the maze to the exit using getMoves() and move().
 As the walker passes through hallways, these are marked by '.'. 
 By calling the solve() function, the Maze will compute the sequence of moves required to
 move from the entrance to the exit of the Maze.

 @author William Hendrix
 */
#ifndef __MAZE_H
#define __MAZE_H

#include <iostream>
#include <deque>
using namespace std;

enum direction_t {UP, RIGHT, LEFT, DOWN, NONE};

typedef struct 
{
  int row;
  int col;
} coordinate_t;

class Maze
{
  friend ostream& operator<<(ostream& out, Maze& m);
private:
  char* maze;
  coordinate_t size;
  coordinate_t start;
  coordinate_t end;
  coordinate_t location;
  int getIndex(coordinate_t loc) const;
public:
  Maze();
  Maze(const Maze& copy);
  Maze(int nrow, int ncol, const char* maze);
  void constructMaze(int nrow, int ncol, const char* maze);
  
  bool isNull() const;
  bool isSolved() const;
  coordinate_t getSize() const;
  coordinate_t getStart() const;
  coordinate_t getEnd() const;
  coordinate_t getLocation() const;

  coordinate_t look(direction_t dir) const;
  bool inBounds(coordinate_t loc) const;
  bool isWalkable(coordinate_t loc) const;
  bool alreadyVisited(coordinate_t loc) const;
  
  bool clearVisited(coordinate_t loc);
  void clearAllVisited();
  void restart();

  void getMoves(bool& up, bool& left, bool& right, bool& down) const;
  bool move(direction_t dir);
  bool move_back(direction_t dir);
  bool solve(deque<direction_t>& solution);
  ~Maze();
};

direction_t reverse(direction_t dir);
bool operator==(coordinate_t lhs, coordinate_t rhs);
bool operator!=(coordinate_t lhs, coordinate_t rhs);

ostream& operator<<(ostream& out, direction_t dir);
ostream& operator<<(ostream& out, deque<direction_t>& moves);
ostream& operator<<(ostream& out, coordinate_t coord);
ostream& operator<<(ostream& out, Maze& m);
#endif
