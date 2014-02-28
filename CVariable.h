//author: Sydney Zink
//teacher: Hendrix

#ifndef __MP5_XCode_2__Calculator__
#define __MP5_XCode_2__Calculator__
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

bool IsCharLetter(const char& c);
bool IsCharDigit(const char& c);
bool IsCharOp(const char& c);

// what is the deal with the above 3 functions and the commmented out enums? (which i deleted...)

class CVariable
{
    friend ostream& operator<<(ostream& out, CVariable& cvar);
private:
    char* name;
    double value;
public:
    CVariable(const char* init_name);
    CVariable(const char* init_name, double init_value);
    CVariable(const CVariable& copy); // copy constructor
    virtual ~CVariable();
    
    // Getters & Setters
    // aka Accessors & Mutators
    const char* getName() const;
    
    // char* Name() const { return name; }; // they gave you this specific definition
    // getters and setters are typically done with camelCase, starting with
    // getX and setX
    // so for value, they would be better named:
    // getValue() instead of Value()
    // setValue() instead of SetValue()
    // but remember, this is JUST a naming convention
    // how you name it doesn't impact functionality
    // your professor just seems to like a specific type of formatting convention
    // (and this is also the convention I am used to for c++)
    bool SetName(const char* name);
    
    
    // reference return creates a value (,,,,wut are you saying?)
    double& Value() { return value; };
    // const ref reture creates a rvalue
    const double& Value() const { return value; };
    void SetValue(const double& v) { value = v; };
    // careful with inline definitions
    // if you include the .h file multiple times
    // your compiler might complain that a function is being redefined
    // i addressed a question like this on piazza awhile ago, but can't remember
    // exactly what error would happen
   
    
    virtual double& operator*();
    virtual double operator*() const;
    //overload =//virtual ... dunno wtf you are saying here haha
    virtual CVariable& operator=(double newValue);
    //also overload =?//virtual ... samesies
    virtual CVariable& operator=(CVariable& newValue);
   
};

class CVarDB
{
    friend ostream& operator<<(ostream& out, CVarDB& cdb);
private:
    vector<CVariable> db;
    //CVariable m_pDB[SIZE_DB];
    int m_nSize; //size of database .... you could just calculate this, no need to save it as far as i can tell...
public:
    CVarDB();
    ~CVarDB();
    bool add(CVariable& newVar);
    void Initialize(); //return a valid ptr if found
    // did they tell you to add Initialize? sounds suspiciously like what a constructor should do...
    CVariable* search(const char* name);
    
};
//First: Check whether op1_name named variable exists in cdb or not. If not, give errror. Else:
//double new_value=cdb[cdb.search(op1_name)].getValue() + atof(op2_name)
//check whether lhs_name named variable exists or not. If yes, edit it. If not, add it to cdb.
//if(cdb.search(lhs_value)!=-1)
//Editing: cdb[cdb.search(lhs.name)].setValue(new_value);
//else
//Adding:cdb.add(lhs_name,value);

ostream& operator<<(ostream& out, CVariable& cvar);
ostream& operator<<(ostream& out, CVarDB& cdb);

/* bool ResolveAStatement(string& state, char* res_name, OP &op, OP_TYPE& type,
 char* operand_1_name, char* operand_2_name, int& count);
 
 // process piece from the buffer from pos pIndex
 int ReadAPiece(const string& buffer, int& pIndex, char* piece); */

#endif