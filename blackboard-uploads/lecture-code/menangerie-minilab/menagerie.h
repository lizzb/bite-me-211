/**
 Class definitions for Bird, Duck, Goose, Toucan, Parrot, and Menagerie

 Bird is an abstract (virtual) class that serves as an interface for the 
 various subtypes of Birds (Ducks, Geese, Toucans, and Parrots).  The primary 
 function of a Bird is to make a birdCall, and the different subtypes of Bird
 will make different calls.  Of these, the Parrot is unique in that each 
 Parrot has special phrase it repeats in its birdCall.  The birdCall of other
 Bird subtypes are indistinguishable from others of the same type aside from
 their names.

 A Menagerie holds a collection of Birds, and its experience() method will
 cause all of them to make their bird calls.
 
 @author William Hendrix
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bird
{
public:
  Bird(string name);
  virtual void birdCall() const; //must be virtual!
protected: //subtype birdCalls would fail if private
  string name; 
};

class Duck : public Bird
{
public:
  Duck(string name);
  virtual void birdCall() const;
};

class Goose : public Bird
{
public:
  Goose(string name);
  virtual void birdCall() const;
};

class Toucan : public Bird
{
public:
  Toucan(string name);
  virtual void birdCall() const;
};

class Parrot : public Bird
{
public:
  Parrot(string name, string quote);
  virtual void birdCall() const;
private:
  string call;
};

class Menagerie
{
public:
  Menagerie();
  Menagerie(const Menagerie& m);
  void addBird(Bird& b);
  void experience() const;
  virtual ~Menagerie();
private:
  vector<Bird*> bird; //must use a vector of Bird*, not Bird, to avoid data shearing with Parrot
  int count; //not necessary with a vector
};
