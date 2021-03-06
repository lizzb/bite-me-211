#include "CVariable.h"
using namespace std;

CVariable::CVariable(const char* init_name)
{
  value = 0.0;

  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}

CVariable::CVariable(const char* init_name, double init_value)
{
  value = init_value;
  
  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}


CVariable::CVariable(const char* init_name, CMatrix init_value)
{
  mval = init_value;
  
  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1); 
}

CVariable::CVariable(const CVariable& copy)
{
  value = copy.value;
  
  int len = strlen(copy.name);
  name = new char[len+1];
  strncpy(name, copy.name, len+1);
}

const char* CVariable::getName() const { return name; }

CVariable::~CVariable() { delete name; }

CVarDB::CVarDB()
{
  CVariable ans("ans");
  db.push_back(ans);
}


/* ----------------------------------------------------------------------------
 Name:     add
 Purpose:  adds a new CVariable to the DB
 Params:   newVar
 Returns:  returns false if the variable name is already taken, true otherwise
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

/*
  //FINISHED AND CORRECT, DO NOT TOUCH // OKAY JEEZ LADY I WON'T
    db.push_back(newVar);
    m_nSize++;
    return 1;
    */

}

bool CVarDB::addNew(const char* name, double value)
{
  if (search(name) == NULL)
  {
    db.push_back(CVariable(name, value));
    return false;
  }
  else return true;
}

bool CVarDB::addNew(const char* name, CMatrix value)
{
  if (search(name) == NULL)
  {
    db.push_back(CVariable(name, value));
    return false;
  }
  else return true;
}


CVariable* CVarDB::search(const char* name)
{
  int len = db.size();
  for (int i = 0; i < len; i++)
    if (strcmp(name, db[i].getName()) == 0)
      return &db[i];

  return NULL;
}

CVariable& CVariable::operator=(double val)
{
  value = val;
  return *this;
}

CVariable& CVariable::operator=(CVariable& cvar)
{
  value = cvar.value;
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

CVarDB::~CVarDB()
{
  //db vector will deconstruct itself
}

ostream& operator<<(ostream& out, CVariable& cvar)
{
  return out << cvar.name << ":\t" << cvar.value;
}

ostream& operator<<(ostream& out, CVarDB& cdb)
{
  cout << "Variables: \n";
  int len = cdb.db.size();
  for (int i = 0; i < len; i++)
    out << cdb.db[i] << endl;
  return out;
}
