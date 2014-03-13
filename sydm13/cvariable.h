#include <iostream>
#include <vector>
#include "Cmatrix.h"
using namespace std;

class CVariable
{
  friend ostream& operator<<(ostream& out, CVariable& cvar);
private:
  char* name;
  CMatrix value;
public:
  CVariable(const char* init_name);
  CVariable(const char* init_name, double init_value); //modify this from lab 5 as now something that constructs a CVariable to store a given scalar value as a 1x1 matrix
  CVariable(const CVariable& copy);
  CVariable(const char* init_name, const CMatrix& init_value); //constructs a new CVariable with the given name that stores a copy of the given CMatrix
  
    const char* getName() const;
    
  CMatrix& operator=(CMatrix& newValue); //sets the CMatrix stored in this CVariable to the given matrix and returns it
    
  CMatrix& operator*(); //returns a reference to the CMatrix stored in this CVariable (replaces double& operator*())
  //virtual double& operator*();

  CMatrix operator*() const; //returns a copy of the CMatrix stored in a const CVariable (replaces double operator*() const)
  //virtual double operator*() const;
    
  CMatrix& operator=(double newValue); //sets the CMatrix stored in this CVariable to a given scalar value (1x1 matrix) and returns a reference to the stored matrix (modification of virtual operator= from lab 5, below)
  //virtual CVariable& operator=(double newValue);
    
  virtual CVariable& operator=(CVariable& newValue);
  virtual ~CVariable();
};

class CVarDB
{
  friend ostream& operator<<(ostream& out, CVarDB& cdb);
private:
  vector<CVariable> db;
public:
  CVarDB();
  bool add(CVariable& newVar);
  bool addNew(const char* name, CMatrix &value);
  CVariable* search(const char* name);
  ~CVarDB();
};

ostream& operator<<(ostream& out, CVariable& cvar);
ostream& operator<<(ostream& out, CVarDB& cdb);
ostream& operator<<(ostream& out, CMatrix& mat);
