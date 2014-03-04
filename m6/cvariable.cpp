/* ----------------------------------------------------------------------------

cvariable.cpp + cvariable.h

Define the classes used to store and manipulate variables


---
cvariable.cpp


Based off Lab 5 Sample Solution

Extended CVariable class 
able to store and manipulate matrix variables using the CMatrix class

---------------------------------------------------------------------------- */

#include "cvariable.h"
using namespace std;

// Constructs a new CVariable with the given name that
// stores a copy of the given CMatrix (new constructor)
CVariable::CVariable(const char* init_name, const CMatrix& init_value)
{

}

// Lab 5 constructor
CVariable::CVariable(const char* init_name)
{
  value = 0.0;

  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}

// Constructs a new CVariable with the given name that
// stores a copy of the given CMatrix (new constructor)
CVariable::CVariable(const char* init_name, const CMatrix& init_value)
{
  //value = init_value;
  
  //int len = strlen(init_name);
  //name = new char[len+1];
  //strncpy(name, init_name, len+1);
}

/* lab 5 version - unclear if this should be replaced with above
or modified to match new type of value
it says "new constructor" so i'll assume its added in */

// Constructs a new CVariable to store a given scalar value
// as a 1x1 matrix (modification)
CVariable::CVariable(const char* init_name, double init_value)
//CVariable::CVariable(const char* init_name, double init_value)
{
  //value = init_value; double can't be assigned to CMatrix or CMatrix* directly
  
  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}

// Lab 5 copy constructor
CVariable::CVariable(const CVariable& copy)
{
  value = copy.value;
  
  int len = strlen(copy.name);
  name = new char[len+1];
  strncpy(name, copy.name, len+1);
}

CVariable::~CVariable()
{
  delete name;
}

const char* CVariable::getName() const
{
  return name;
}



// Set this CVariable's CMatrix to the given matrix and return it
//CVariable& CVariable::operator=(CVariable& cvar)
CMatrix& CVariable::operator=(CMatrix& newValue)
{
  // need to modify - check return type
  // value = newValue;
  // return *this; 
}


// Set the CMatrix stored in this CVariable to a 
// given scalar value (1x1 matrix) and
// return a reference to the stored matrix (modification)
CMatrix& CVariable::operator=(double newValue)
{
  // need to adjust, - check return type 
  // this is from lab 5 basis 
  // CVariable& CVariable::operator=(double val)
  //value = newValue;
  //return *this;
}



/*
LAB 5 versions - updated to below for lab 6
since the type changes of member variable "value" from double to either CMatrix or CMatrix*

CVariable& CVariable::operator=(CVariable& cvar)
{
  value = cvar.value;
  return *this;
}

CVariable& CVariable::operator=(double val)
{
  value = val;
  return *this;
}

double& CVariable::operator*()
{
  return value;
}

double CVariable::operator*() const
{
  return value;
}

*/


// Returns a reference to the CMatrix stored in this CVariable
// (replaces double& operator*())
CMatrix& CVariable::operator*()
{


}

// Returns a copy of the CMatrix stored in a const CVariable 
// (replaces double operator*() const)
CMatrix CVariable::operator*() const
{
  return value;
}

/* ----------------------------------------------------------------------------

Based off Lab 5 Sample Solution

CVarDB class to help organize and retrieve user-defined variables for your Mini-Matlab program.

The CVarDB class should store and manage the collection of all currently defined variables in a vector.
(The CVarDB should also manage the "automatic" variable ans.)

---------------------------------------------------------------------------- */



CVarDB::CVarDB()
{
  CVariable ans("ans");
  db.push_back(ans);
}

CVarDB::~CVarDB()
{
  //db vector will deconstruct itself
}

bool CVarDB::add(CVariable& cvar)
{
  if (search(cvar.getName()) == NULL)
  {
    db.push_back(cvar);
    return false;
  }
  else
    return true;
}

bool CVarDB::addNew(const char* name, double value)
{
  if (search(name) == NULL)
  {
    db.push_back(CVariable(name, value));
    return false;
  }
  else
    return true;
}

CVariable* CVarDB::search(const char* name)
{
  int len = db.size();
  for (int i = 0; i < len; i++)
    if (strcmp(name, db[i].getName()) == 0)
      return &db[i];

  return NULL;
}


// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar)
{
  return out << cvar.name << ":\t" << cvar.value;
}

// prints out every CVariable in the DB
ostream& operator<<(ostream& out, CVarDB& cdb)
{
  cout << "Variables: \n";
  int len = cdb.db.size();
  for (int i = 0; i < len; i++)
    out << cdb.db[i] << endl;
  return out;
}
