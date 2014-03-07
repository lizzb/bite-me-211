/**
 Implements methods for Bird, Duck, Goose, Toucan, Parrot, and Menagerie classes defined in menagerie.h
 See menagerie.h for more details.  Not recommended for those allergic to whimsy.

 @author William Hendrix
 */

#include "menagerie.h"

/**
 Basic constructor for Bird; sets the Bird's name

 @param name the name of this Bird
 */
Bird::Bird(string name)
{
  //Note:  we need to use this->name to refer to the data member, as name refers to the parameter
  this->name = name;
}

/**
 Basic constructor for a Duck

 @param name the Duck's name
 */
Duck::Duck(string name):Bird(name) {}

/**
 Basic constructor for a Goose

 @param name the Goose's name
 */
Goose::Goose(string name):Bird(name) {}

/**
 Basic constructor for a Toucan

 @param name the Toucan's name
 */
Toucan::Toucan(string name):Bird(name) {}

/**
 Basic constructor for a Parrot

 @param name the Parrot's name
 @param quote the phrase that the Parrot repeats during its birdCall
 */
Parrot::Parrot(string name, string quote):Bird(name)
{
  call = quote;
}

/**
 Prints out a generic bird call
 Bird objects should generally belong to a specialized type, so this should rarely be called
 */
void Bird::birdCall() const
{
  cout << name << " chirps plaintively.\n";
}

/**
 Prints out a Duck's bird call
 */
void Duck::birdCall() const
{
  cout << "A duck named " << name << " quacks.\n";
}

/**
 Prints out a Goose's bird call
 */
void Goose::birdCall() const
{
  cout << "A goose named " << name << " honks with abandon.\n";
}

/**
 Prints out a Toucan's bird call
 */
void Toucan::birdCall() const
{
  cout << "A toucan named " << name << " caws from its perch.\n";
}

/**
 Prints out a Parrot's bird call
 */
void Parrot::birdCall() const
{
  cout << "A parrot named " << name << " says, \"" << call << "\"\n";
}

/**
 Constructs an empty Menagerie
 */
Menagerie::Menagerie()
  :bird()
{
  count = 0;
}

/**
 Copy constructor for Menagerie
 Not used by menagerie_driver.cpp, but good practice to define ourselves

 @param m the Menagerie to copy
 */
Menagerie::Menagerie(const Menagerie& m)
  :bird(NULL, m.count)
{
  count = m.count;
  bird = m.bird;
  //We only use a shallow copy here, as we do not know the "true class" of the Birds in bird
  //A better solution might be use a virtual Bird.copy() function to create a deep copy of the Menagerie
}

/**
 Adds a Bird to the Menagerie

 @param b the Bird to add
 */
void Menagerie::addBird(Bird& b)
{
  bird.push_back(&b);
  //Note: if the Bird from the calling function is destroyed, our vector may become corrupted
  count++;
}

/**
 Prints a bird call for every Bird in the Menagerie
 */
void Menagerie::experience() const
{
  cout << "You are in a menagerie.\n";
  for (int i = 0; i < count; i++)
    bird[i]->birdCall();  //Polymorphic behavior
}

/**
 Menagerie destructor
 */
Menagerie::~Menagerie()
{
  //If we were using an array of Birds*, we would deallocate it here
  //If we were not using shallow copying, we would also delete the Birds inside
}
