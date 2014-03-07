/**
 Implementation for Maze class
 This class represents a maze as a rectangular grid of characters that is traversed by a walker.
 
 @author William Hendrix
 */

#include "maze.h"
using namespace std;

/**
 Constructs a null Maze
 Use the construct() function to set up the Maze
 */
Maze::Maze()
{
  size.col = size.row = -1;
  location = start = end = size;
  maze = NULL;
}

/**
 Constructs an nrow by ncol maze
 Mazes are represented by a grid of cells, where each cell may be a hallway (' '), wall ('#'), the maze entrance ('S'), or the maze exit ('E').
 A Maze should have exactly one entrance and exit.
 The Maze also stores a "walker" who starts at the Maze entrance.
 The Maze is specified by a string where the cells are read in row-wise (left-to-right, top-to-bottom). 
 Newline characters in the string to represent the start of a new row are optional.

 @param nrow the number of rows in the Maze
 @param ncol the number of columns in the Maze
 @param maze the string representation of the Maze to construct
 */
Maze::Maze(int nrow, int ncol, const char* maze)
{
  this->maze = NULL;
  constructMaze(nrow, ncol, maze);
}

/**
 Copy constructor for Maze
 */
Maze::Maze(const Maze& copy)
{
  if (!copy.isNull())
  {
    size = copy.size;
    location = copy.location;
    start = copy.start;
    end = copy.end;
    maze = new char[size.row*size.col];
    strncpy(maze, copy.maze, size.row*size.col);
  }
  else
  {
    size.col = size.row = -1;
    location = start = end = size;
    this->maze = NULL;
  }
}

/**
 Maze destructor
 */
Maze::~Maze()
{
  if (maze != NULL)
    delete maze;
}

/**
 "Re-constructs" the Maze to become a different Maze.  See 3-value constructor for more details.

 @param nrow the number of rows in the Maze
 @param ncol the number of columns in the Maze
 @param maze the string representation of the new Maze
 */
void Maze::constructMaze(int nrow, int ncol, const char* maze)
{
  if (this->maze != NULL)
    delete this->maze;

  size.row = nrow;
  size.col = ncol;
  start.row = start.col = -1;
  end = start;

  bool invalid = false;
  int n = 0;
  if (nrow * ncol > 0)
    this->maze = new char[nrow*ncol];
  for (int r = 0; r < nrow; r++)
    for (int c = 0; c < ncol; c++)
    {
      while (maze[n] == '\n' || maze[n] == '\r') //Ignore new lines
        n++;

      char curr = maze[n];
      n++;
      switch (curr)
      {
      case 'S': //Start of maze
      case 's':
        if (start.row != -1) //Check for multiple entrances
          invalid = true;
        start.row = location.row = r;
        start.col = location.col = c;
        this->maze[r*ncol+c] = 'S';
        break;
      case 'E': //End of maze
      case 'e':  
        if (end.row != -1) //Check for multiple exits
          invalid = true;
        end.row = r;
        end.col = c;
        this->maze[r*ncol+c] = 'E';
        break;
      case '#': //Walls
        this->maze[r*ncol+c] = '#';
        break;
      case ' ': //Space
      case '.':
        this->maze[r*ncol+c] = ' ';
        break;
      default: //Null character 
        invalid = true;
      }

      if (invalid)
      {
        size.row = size.col = -1;
        location = size;
        delete this->maze;
        return;
      }
    }
  
  if (end.row == -1 || start.row == -1) //Check to make sure entrance and exit were set
  {
    size.row = size.col = -1;
    location = size;
  }
}

/**
 Tests whether the Maze was improperly initialized

 @return whether the Maze is invalid
 */
bool Maze::isNull() const
{
  return size.row == -1;
}

/**
 Private helper function that calculates the offset in the maze matrix for the given coordinate

 @param loc the location to calculate the offset for
 @return the offset
 */
int Maze::getIndex(coordinate_t loc) const
{
  return loc.row * size.col + loc.col; 
}

/**
 Tests whether the Maze walker is at the exit

 @return whether the Maze is solved
 */
bool Maze::isSolved() const
{
  return !isNull() && location == end;
}

/**
 Returns the size (# rows, # cols) of the Maze

 @return the size of the Maze
 */
coordinate_t Maze::getSize() const
{
  return size;
}

/**
 Returns the current location of the Maze "walker"

 @return the current location
 */
coordinate_t Maze::getLocation() const
{
  return location;
}

/**
 Returns the location of the Maze entrance ('S')

 @return the location of the Maze entrance
 */
coordinate_t Maze::getStart() const
{
  return start;
}

/**
 Returns the location of the Maze exit ('E')

 @return the location of the Maze exit
 */
coordinate_t Maze::getEnd() const
{
  return end;
}

/**
 Returns Boolean values to indicate whether the Maze walker can move up, down, left, or right
 Will not allow walker to walk off of Maze or into a wall
 Will also not allow walker to revisit a visited cell in the Maze

 @param up    (output param) whether the walker can move UP
 @param left  (output param) whether the walker can move LEFT
 @param right (output param) whether the walker can move RIGHT
 @param down  (output param) whether the walker can move DOWN
 */
void Maze::getMoves(bool& up, bool& right, bool& left, bool& down) const
{
  int index = getIndex(location);

  //More efficient than using look(), isWalkable(), and alreadyVisited(), but less flexible to changes in implementation
  up    = location.row > 0            && (maze[index - size.col] == ' ' || maze[index - size.col] == 'E');
  down  = location.row < size.row - 1 && (maze[index + size.col] == ' ' || maze[index + size.col] == 'E');
  left  = location.col > 0            && (maze[index - 1] == ' '        || maze[index - 1] == 'E');
  right = location.col < size.col - 1 && (maze[index + 1] == ' '        || maze[index + 1] == 'E');
}

/**
 Tests whether the given coordinates fall inside the maze

 @param loc the location to test
 @return whether or not that location represents a valid Maze cell
 */
bool Maze::inBounds(coordinate_t loc) const
{
  return loc.row >= 0 && loc.row < size.row && loc.col >= 0 && loc.col < size.col;
}

/**
 Tests whether a given cell in the Maze is "walkable"
 Cell must not be a wall and it must be in the Maze

 @param loc the row and column of the cell to test
 @return whether that cell is walkable
 */
bool Maze::isWalkable(coordinate_t loc) const
{
  if (!inBounds(loc))
    return false;

  int index = getIndex(loc);
  return maze[index] != '#';
}

/**
 Tests whether the walker has already visited the given cell
 Cells outside the bounds of the Maze will return false
 The Maze exit is always considered unvisited, while the entrance is always considered visited

 @param loc the row and column of the cell to test
 @return whether that cell has already been visited by the walker
 */
bool Maze::alreadyVisited(coordinate_t loc) const
{
  if (!inBounds(loc))
    return false;

  int index = getIndex(loc);
  return maze[index] == '.' || maze[index] == 'S';
}

/**
 Convenience function that returns the coordinate in the given direction from the walker
 Returns the coordinate (-1, -1) if this direction would cause the walker to walk off of the Maze

 @param dir the direction in which to look
 @return the coordinate in that direction
 */
coordinate_t Maze::look(direction_t dir) const
{
  coordinate_t ret = location;
  switch (dir)
  {
  case UP:
    ret.row--;
    break;
  case DOWN:
    ret.row++;
    break;
  case LEFT:
    ret.col--;
    break;
  case RIGHT:
    ret.col++;
    break;
  default:
    ret = location;
  }

  if (!inBounds(ret))
    ret.row = ret.col = -1;

  return ret;
}

/**
 Moves the walker in the indicated direction
 Will not move walker off edge of Maze or into a Wall

 @param dir the direction in which to move the walker
 @return whether the move can be made
 */
bool Maze::move(direction_t dir)
{
  coordinate_t target = look(dir);
  if (!isWalkable(target))
    return false;

  int index = target.row*size.col+target.col;
  location = target;

  if (maze[index] != 'E')
    maze[index] = '.'; //Mark current location as visited
  return true;
}

/**
 "Undoes" a move by the walker
 The cell in the opposite direction must have been previously visited by the walker, 
 but the Maze does not truly "know" that this is which direction the walker walked previously
 Could potentially "leave behind" visited cells if the path is not reversed correctly

 @param dir the direction that the walker moved to reach its current location
 @return whether the move could be undone successfully
 */
bool Maze::move_back(direction_t dir)
{
  direction_t rev = reverse(dir);
  coordinate_t back = look(rev);

  //Check whether move is valid
  if (isWalkable(back) && alreadyVisited(back))
  {
    //if (location.row != end.row || location.col != end.col)
    //  maze[location.row*size.col+location.col] = ' '; //Mark current location as unvisited

    move(rev); //Will succeed
    return true;
  }
  else
    return false;
}

/**
 Clears the "visited" state for the hallway at the given location
 Will fail if clearing the visited status of an invalid location, an unvisited location, 
 the Maze entrance, or the walker

 @param loc the location to clear the visited status
 @
 */
bool Maze::clearVisited(coordinate_t loc)
{
  if (alreadyVisited(loc) && loc != start)
  {
    int index = getIndex(loc);
    maze[index] = ' ';
    return true;
  }
  else
    return false;
}

/**
 Clears the "visited" state for every hallway in the Maze
 */
void Maze::clearAllVisited()
{
  if (!isNull())
  {
    int numel = size.row * size.col;
    for (int n = 0; n < numel; n++)
      if (maze[n] == '.')
        maze[n] = ' ';
  }
}

/**
 Restarts the walker at the Maze entrance and clears all "visited" cells
 */
void Maze::restart()
{
  location = start;
  clearAllVisited();
}

/**
 Outputs the given Maze to the given output stream
 Legend:  '#' Wall
          ' ' Non-visited hallway
          '.' Visited hallway
          'S' Maze entrance
          'E' Maze exit
 
 @param out the output stream to which we print the given Maze
 @param m the Maze to print
 @return the output stream
 */
ostream& operator<<(ostream& out, Maze& m)
{
  if (!m.isNull())
  {
    int numel = m.size.row * m.size.col;
    int locidx = m.getIndex(m.location);
    for (int n = 0; n < numel; n++)
    {
      if (n % m.size.col == 0)
        out << '\n';
      if (n == locidx && (m.maze[n] == ' ' || m.maze[n] == '.'))
        out << '*';
      else
        out << m.maze[n];
    }
  }
  else
    out << "Empty maze";

  return out << endl;
}

/**
 Prints a text representation of a direction_t to a given output stream
 
 @param out the output stream
 @param dir the direction_t to print
 @return the output stream
 */
ostream& operator<<(ostream& out, direction_t dir)
{
  switch (dir)
  {
  case UP:
    out << "up";
    break;
  case DOWN:
    out << "down";
    break;
  case LEFT:
    out << "left";
    break;
  case RIGHT:
    out << "right";
    break;
  default:
    out << "Invalid direction";
    break;
  }

  return out;
}

/**
 Prints a sequence of moves in a deque to a given output stream

 @param out the output stream
 @param moves the sequence of moves to print
 @return the output stream
 */
ostream& operator<<(ostream& out, deque<direction_t>& moves)
{
  if (!moves.empty())
    out << moves[0];
  for (int i = 1; i < moves.size(); i++)
    out << ", " << moves[i];

  return out;
}

/**
 Prints a coordinate_t to a given output stream

 @param out the output stream
 @param coord the coordinate_t to print
 @return the output stream
 */
ostream& operator<<(ostream& out, coordinate_t coord)
{
  return out << '(' << coord.row << ", " << coord.col << ')';
}

/**
 Evaluate equality for two coordinate_t structs

 @param lhs one of the coordinates to compare
 @param rhs the other coordinate to compare
 @return whether they are the same location
 */
bool operator==(coordinate_t lhs, coordinate_t rhs)
{
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

/**
 Evaluate inequality for two coordinate_t structs

 @param lhs one of the coordinates to compare
 @param rhs the other coordinate to compare
 @return whether they are different locations
 */
bool operator!=(coordinate_t lhs, coordinate_t rhs)
{
  return lhs.row != rhs.row || lhs.col != rhs.col;
}

/**
 Convenience function that returns the reverse of the given direction

 @param the direction to reverse
 @return the reversed direction
 */
direction_t reverse(direction_t dir)
{
  direction_t reverse;
  switch (dir)
  {
  case UP:
    reverse = DOWN;
    break;
  case DOWN:
    reverse = UP;
    break;
  case LEFT:
    reverse = RIGHT;
    break;
  case RIGHT:
    reverse = LEFT;
    break;
  default:
    return NONE;
  }

  return reverse;
}

/**
 Searches for Maze exit from current location using backtracking (depth-first) search
 Returns false if cannot find Maze exit before exhausting moves

 @param solution (output parameter) the list of moves required to move to the Maze exit
 @return whether the solution attempt was successful
 
 @author <YOUR_NAME_HERE>
 */
bool Maze::solve(deque<direction_t>& solution)
{
  //TODO:  solve the maze using a deque of direction_t and return the solution
  //Hint:  if you find the exit, your stack will contain the solution
  
  return false;
}
