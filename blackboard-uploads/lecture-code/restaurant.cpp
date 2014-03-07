#include <iostream>
using namespace std;

/**
  Program for ordering food from a restaurant
  
  Note that dollar amounts are not rounded to two places, as we have not yet
  covered how to do this.  Also, this implementation uses "magic numbers",
  which we will discuss later.
 */
int main()
{
  double bill = 0.0;
  int select;

  cout << "Welcome!  Please select what you'd like to order from the following menu:" << endl
       << "(1) Mussels     $11.95" << endl
       << "(2) Crab cake   $13.95" << endl
       << "(3) Salmon      $24.95" << endl
       << "(4) Tilapia     $17.95" << endl
       << "(5) Cheesecake  $ 7.95" << endl
       << "(q) Finished ordering"  << endl << endl;

  do
  {
    cout << "Current bill:  $" << bill << endl
         << "Enter a selection (or q to end): ";
    cin >> select;

    if (!cin.fail())
    {
      switch (select)
      {
      case 1:
        cout << "You've selected the mussels" << endl;
        bill += 11.95;
        break;
      case 2:
        cout << "You've selected the crab cake" << endl;
        bill += 13.95;
        break;
      case 3:
        cout << "You've selected the salmon" << endl;
        bill += 24.95;
        break;
      case 4:
        cout << "You've selected the tilapia" << endl;
        bill += 17.95;
        break;
      case 5:
        cout << "You've selected the cheesecake" << endl;
        bill += 7.95;
        break;
      default:
        cout << "Invalid choice; pick again" << endl;
        break;
      }
    }
  } while (!cin.fail());
  cin.clear();
  cin.sync();

  cout << endl 
       << "Subtotal:  $" << bill << endl
       << "Tax:       $" << bill * 0.11 << endl
       << "Gratuity:  $" << bill * 0.18 << endl
       << "==================" << endl
       << "Total:     $"  << bill * (1 + 0.11 + 0.18) << endl;

  char c;
  cout << "Type 'q' to quit: ";
  cin >> c;
  return 0;
}