#include <iostream>
using namespace std;

/**
  Example program for playing Nim with two players
  The game starts with 21 stones, and players take turns
  removing 1-3 stones.  The last player to make a move loses!
 */

int main(int argc, char** argv)
{
    cout << "Welcome to Nim!" << endl << endl;
    int stones = 21;
    int remove = 0;
    int playerTracker = 1; // Keeps track of the current player
    int winner;
    
    cout << "There are 21 stones." << endl;
    while (true)
    {
        cout << "Player " << playerTracker << ", remove 1-3 stones: ";
        cin >> remove;
        if (!cin.fail() && remove < 4 && remove > 0)
        {
            stones -= remove;
            if (stones <= 0)
                break;
            cout << "Player " << playerTracker << " removed " << remove << " stones. There are " << stones << " stones left."<< endl << endl;
            if (playerTracker == 1)
                playerTracker = 2;
            else
                playerTracker = 1;
        }
        else
        {
          cout << "Bad number of stones." << endl;
          cin.clear();
        }
        cin.sync();
    }
    
    if (playerTracker == 1)
        winner = 2;
    else
        winner = 1;
    cout << endl << "There are 0 stones left." << endl;
    cout << "Player " << winner << " WON!!!" << endl;

    char c;
    cout << "Type 'q' to quit: ";
    cin >> c;
    return 0;
}
