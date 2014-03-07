/**
 Test driver for Maze class
 Constructs a sample Maze, solves that Maze, and print the result

 @author William Hendrix
 */
#include <iostream>
#include "maze.h"

int main()
{
  Maze maze(8, 8, "\
    #  E\n\
 ###  ##\n\
   # #  \n\
## #   #\n\
   ###  \n\
 #    # \n\
# ## #  \n\
S      #");
  deque<direction_t> sol;

  cout << maze << endl;

  if (maze.solve(sol))
    cout << "Solution using a stack: " << sol << '\n' << maze << endl;
  else
    cout << "This maze is not solvable!" << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}
