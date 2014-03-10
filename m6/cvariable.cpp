/* ----------------------------------------------------------------------------

cvariable.cpp

Extended CVariable class (based off Lab 5 Sample Solution)

able to store and manipulate matrix variables using the CMatrix class

---------------------------------------------------------------------------- */
#include "cmatrix.h"
#include "cvariable.h"
using namespace std;

// Constructs a new CVariable with the given name that
// stores a copy of the given CMatrix
// (new constructor)
/*CVariable::CVariable(const char* init_name, const CMatrix& init_value)
{

}*/

// Lab 5 constructor
CVariable::CVariable(const char* init_name)
{
  value = 0.0;

  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}

// Constructs a new CVariable with the given name that
// stores a copy of the given CMatrix
// (new constructor)
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
// as a 1x1 matrix
// (modification)
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

// Destructor
CVariable::~CVariable()
{
  delete name;
}

const char* CVariable::getName() const  // this is wrong
{
  return name;
}


/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// Set this CVariable's CMatrix to the given matrix and return it
/*CVariable& CVariable::operator=(CVariable& cvar) {return null; } //.... or keep this?
CMatrix& CVariable::operator=(CMatrix& newValue)
{
  // need to modify - check return type
  // value = newValue;
  // return *this;
    return null;
}
*/

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// Set the CMatrix stored in this CVariable to a 
// given scalar value (1x1 matrix) and
// return a reference to the stored matrix
// (modification)
CMatrix& CVariable::operator=(double newValue)
{
  // need to adjust, - check return type 
  // this is from lab 5 basis 
  // CVariable& CVariable::operator=(double val)
  //value = newValue;
  //return *this;
  //  return null;
  //  return value;
}

CVariable& CVariable::operator=(CVariable& newValue)
{
    
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
// Returns a reference to the CMatrix stored in this CVariable
CMatrix& CVariable::operator*() // (replaces double& operator*())
{


}


// Returns a copy of the CMatrix stored in a const CVariable 
CMatrix CVariable::operator*() const // (replaces double operator*() const)
{
  return value;
}

/* ----------------------------------------------------------------------------

Based off Lab 5 Sample Solution

CVarDB class to help organize and retrieve
user-defined variables for your Mini-Matlab program.

The CVarDB class should store and manage the collection
of all currently defined variables in a vector.
(The CVarDB should also manage the "automatic" variable ans.)

---------------------------------------------------------------------------- */


/*
 * Name:        CTileCoalmine::CTileCoalmine()
 * Description: The constructor for the coal mine
 * Parameters:  CCity city
 * Returns:     none
 */
CVarDB::CVarDB()
{
  CVariable ans("ans");
  db.push_back(ans);
}

CVarDB::~CVarDB()
{
  //db vector will deconstruct itself
}

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
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

/* ----------------------------------------------------------------------------
 Name:     
 Purpose:  
 Params:   
 Returns:  
 ---------------------------------------------------------------------------- */
CVariable* CVarDB::search(const char* name)
{
  int len = db.size();
  for (int i = 0; i < len; i++)
    if (strcmp(name, db[i].getName()) == 0)
      return &db[i];

  return NULL;
}


/* ----------------------------------------------------------------------------
 Name:     add
 Purpose:  adds a new CVariable to the DB
 Params:   newVar
 Returns:  returns false if the variable name is already taken, true otherwise
 ---------------------------------------------------------------------------- */
// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar)
{
    return out << cvar.name << ":\t";// << printMatrix(cvar.value);//cvar.value;
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
