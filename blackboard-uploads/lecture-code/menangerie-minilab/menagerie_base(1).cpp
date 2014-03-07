#include "menagerie.h"

Bird::Bird(string name)
{
  this->name = name;
}

Duck::Duck(string name):Bird(name) {}
Goose::Goose(string name):Bird(name) {}
Toucan::Toucan(string name):Bird(name) {}
Parrot::Parrot(string name, string quote):Bird(name)
{
  call = quote;
}

Bird::birdCall() const
{
  cout << name << " chirps plaintively.\n";
}

void Duck::birdCall() const
{
  cout << "A duck named " << name << " quacks.\n";
}

void Goose::birdCall() const
{
  cout << "A goose named " << name << " honks with abandon.\n";
}

void Toucan::birdCall() const
{
  cout << "A toucan named " << name << " caws from its perch.\n";
}

void Parrot::birdCall() const
{
  cout << "A parrot named " << name << " says, \"" << call << "\"\n";
}

Menagerie::Menagerie()
{
  //TODO:  Fill in this function
}

void Menagerie::addBird(Bird& b)
{
  //TODO:  Fill in this function
}

void Menagerie::experience() const
{
  cout << "You are in a menagerie.\n";
  for (int i = 0; i < count; i++)
    ; //TODO:  Call birdCall() on bird[i] here
}

Menagerie::~Menagerie()
{
}
