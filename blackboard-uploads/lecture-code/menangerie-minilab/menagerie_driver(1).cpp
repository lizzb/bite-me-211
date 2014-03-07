/**
 Example program demonstrating inheritance, virtual functions, and polymorphic behavior

 @author William Hendrix
 */

#include <iostream>
using namespace std;

#include "menagerie.h"

int main()
{
  Duck bernard("Bernard");
  Parrot polly("Polly", "How do you do?");
  Toucan sam("Sam");
  Goose gertrude("Gertrude");

  Menagerie mildredsMenagerie;
  mildredsMenagerie.addBird(bernard);
  mildredsMenagerie.addBird(polly);
  mildredsMenagerie.addBird(sam);
  mildredsMenagerie.addBird(gertrude);

  mildredsMenagerie.experience();

  char c;
  cout << "Enter  'q' to quit: ";
  cin >> c;

  return 0;
}
