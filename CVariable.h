#include <iostream>
#include <vector>
using namespace std;

// http://pastebin.com/RsXRT4n9

class CVariable
{
  friend ostream& operator<<(ostream& out, CVariable& cvar);
private:
  char* name;
  double value;
public:
  CVariable(const char* init_name);
  CVariable(const char* init_name, double init_value);
  CVariable(const CVariable& copy);
  const char* getName() const;
  virtual double& operator*();
  virtual double operator*() const;
  virtual CVariable& operator=(double newValue);
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
  CVariable* search(const char* name);
  ~CVarDB();
};

ostream& operator<<(ostream& out, CVariable& cvar);
ostream& operator<<(ostream& out, CVarDB& cdb);