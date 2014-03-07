/* ----------------------------------------------------------------------------
nvjhfhkvkhkhjgkjhgkhgkhjgkjhgkjhg
Based off Lab 5 Sample Solution

The CVariable class should store the name and value of a user-defined variable.
represent the variables defined by the user
...allow CVariable to store and manipulate CMatrix values...

Extended CVariable class 
able to store and manipulate matrix variables using the CMatrix class

---------------------------------------------------------------------------- */

#include <iostream>
#include <vector>
using namespace std;

class CVariable
{
  friend ostream& operator<<(ostream& out, CVariable& cvar);

private:
  /*
  LAB 5
  As we are not going to incorporate matrix operations in this assignment, (m5)
  you can use a double to store the variable value
  and a char array (char*) to hold the name.
  */
  char* name;     // store the name of the variable 
  //double value;   // store the variable value

  /*
  LAB 6
  The choice of how you wish to represent scalar and matrix values
  inside a CVariable object may make certain operations simpler or more complex.
  One way to implement this:
  change the value field of your CVariable class
  to have type CMatrix or CMatrix*
  rather than double, using "has-a" inheritance. 
  ---- i'm sure that everyone completely understands what this means -_-
  */

  CMatrix value;
  // not yet clear to me if CMatrix or CMatrix* is what prof has in mind
  

public:

  // Constructs a new CVariable with the given name that
  // stores a copy of the given CMatrix
  // (new constructor)
  CVariable::CVariable(const char* init_name, const CMatrix& init_value);
  
  // Initializes a CVariable - with a given name and value 0
  CVariable(const char* init_name);
  

  // Constructs a new CVariable to store a given scalar value
  // as a 1x1 matrix
  // (modification)
  // LAB 5 (OLD): Initializes a CVariable - with a given name and value
  // CVariable(const char* init_name, double init_value);
  CVariable::CVariable(const char* init_name, double init_value);

  
  
  // Copy constructor
  CVariable(const CVariable& copy);

  // Destructor - destroys the CVariable
  // side - i have no idea why virtual is included in this declaration,
  // because it wasn't in the spec for lab 5 .h file
  virtual ~CVariable();

  // return the name of this CVariable
  const char* getName() const;


  // Returns a reference to the CMatrix stored in this CVariable
  // (replaces double& operator*())
  CMatrix& operator*();

  // LAB 5
  // return a reference to the value stored in this CVariable
  //virtual double& operator*();


  // Returns a copy of the CMatrix stored in a const CVariable 
  // (replaces double operator*() const)
  CMatrix operator*() const;

  // LAB 5
  // return the value stored in a const CVariable
  //virtual double operator*() const;


// Returns a reference to the CMatrix stored in this CVariable
// (replaces double& operator*())
//CMatrix& CVariable::operator*()

// Returns a copy of the CMatrix stored in a const CVariable 
// (replaces double operator*() const)
//CMatrix CVariable::operator*() const
  
  // Sets the CMatrix stored in this CVariable to a 
  // given scalar value (1x1 matrix) and
  // returns a reference to the stored matrix
  // (modification)
  // LAB 5 (OLD): set the value of this CVariable (returns the CVariable)
  virtual CVariable& operator=(double newValue);

  // Set the value of this CVariable to match that of the given CVariable (returns the CVariable)
  virtual CVariable& operator=(CVariable& newValue);

  // Sets the CMatrix stored in this CVariable to
  // the given matrix and returns it
  // (new function)
  CMatrix& operator=(CMatrix& newValue); 
  
};


// THIS IS STILL DISGUSTING
// YOU'RE NOT SUPPOSED TO DEFINE 2 CLASSES IN ONE .H FILE UGHHHGHHGHGASDJFALS;KDFJ
class CVarDB
{
  friend ostream& operator<<(ostream& out, CVarDB& cdb);
private:
  vector<CVariable> db;
public:
  // Initializes the variable database to contain only the ans variable
  CVarDB();

  // Destructor - destroys the DB
  ~CVarDB();

  // adds a new CVariable to the DB;
  // returns false if the variable name is already taken
  bool add(CVariable& newVar);
  bool addNew(const char* name, double value); // this wasn't in the lab5 spec so its a helper fx

  // returns a pointer to the CVariable in the DB with the given name
  // or NULL if not found
  CVariable* search(const char* name);

};

// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar);

// prints out every CVariable in the DB
ostream& operator<<(ostream& out, CVarDB& cdb);
