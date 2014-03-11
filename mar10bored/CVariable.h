#include <iostream>
#include <vector>
using namespace std;

#include "CMatrix.h"

class CVariable
{
  friend ostream& operator<<(ostream& out, CVariable& cvar);
private:
  char* name;     // Name of this variable
  CMatrix value;  // The matrix this variable holds
  //double value;
  //CMatrix mval;
public:
  CVariable(const char* init_name);
  CVariable(const char* init_name, double init_value);  // NEED TO MODIFY
  CVariable(const CVariable& copy);
  const char* getName() const;
  //virtual double& operator*();
  //virtual double operator*() const;
  virtual CVariable& operator=(double newValue);
  virtual CVariable& operator=(CVariable& newValue);
  virtual ~CVariable();



//CMatrix& operator*();
//returns a reference to the CMatrix stored in this CVariable
//(replaces double& operator*())
//CMatrix operator*() const;
//returns a copy of the CMatrix stored in a const CVariable
//(replaces double operator*() const)

CVariable(const char* init_name, CMatrix init_matrix);
//  CVariable(const char* init_name, const CMatrix& init_value);
// constructs a new CVariable with the given name
// that stores a copy of the given CMatrix (new constructor)

  virtual CVariable& operator=(CMatrix newValue);
  virtual CMatrix& operator*();
  virtual CMatrix operator*() const;

};

class CVarDB
{
  friend ostream& operator<<(ostream& out, CVarDB& cdb);
private:
  vector<CVariable> db;
public:
  CVarDB();
  ~CVarDB();
  CVariable* search(const char* name);

  bool add(CVariable& newVar);
  //bool addNew(const char* name, double value);
  bool addNew(const char* name, CMatrix value);
};

ostream& operator<<(ostream& out, CVariable& cvar);
ostream& operator<<(ostream& out, CVarDB& cdb);
