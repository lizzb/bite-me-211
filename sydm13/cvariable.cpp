#include <cstring>
#include "cvariable.h"
using namespace std;

CVariable::CVariable(const char* init_name)
{
  value = CMatrix(0.0);

  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
}

CVariable::CVariable(const char* init_name, double init_value)
{
  
  int len = strlen(init_name);
  name = new char[len+1];
  strncpy(name, init_name, len+1);
  
    
  value = CMatrix(init_value);
}

CVariable::CVariable(const CVariable& copy) // copy constructor?!!? ***
{
  value = copy.value;
  
  int len = strlen(copy.name);
  name = new char[len+1];
  strncpy(name, copy.name, len+1);
}

CVariable::CVariable(const char* init_name, const CMatrix& init_value)
{
    //cout<<"AMG"<<value;
    int len = strlen(init_name);
    name = new char[len+1];
    strncpy(name, init_name, len+1);
    value = init_value;
}

const char* CVariable::getName() const
{
  return name;
}

CVariable::~CVariable()
{
  delete name;
    //value.~CMatrix();
}

CVarDB::CVarDB()
{
  CVariable ans("ans");
  db.push_back(ans);
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

bool CVarDB::addNew(const char* name, CMatrix &value)
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

CMatrix& CVariable::operator=(double val)
{
  value = val;
  return value;
}

CMatrix& CVariable::operator=(CMatrix& newValue)
{
    value = newValue;
    //value.operator=(newValue);  //Same as the previous line
    return value;
}

CVariable& CVariable::operator=(CVariable& cvar)
{
  value = cvar.value;
  return *this;
}

/* double& CVariable::operator*()
{
  return value;
} */

CMatrix& CVariable::operator*() //replaces double& operator*()
{
    return value;
}

/* double CVariable::operator*() const
{
  return value;
} */

CMatrix CVariable::operator*() const //replaces double operator*() const
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
  int len = (cdb.db).size();
  for (int i = 0; i < len; i++)
    out << cdb.db[i] << endl;
  return out;
}

ostream& operator<<(ostream& out, CMatrix& mat)
{
    if (mat.IsNull())
		out << "\tnull matrix" << std::endl;
	else
	{
		// row by row
		for (int i = 0; i < mat.getNRow(); ++i)
		{
			//out << "\t";
			for (int j = 0; j < mat.getNCol(); ++j)
				out << mat.element(i, j) << "\t";
			out << std::endl;
		}
	}
	out << std::endl;
    return out;
}
