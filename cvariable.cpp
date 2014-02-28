//
//  cvariable.cpp
//  Lab 5 Due 22414 SGZ
//
//  Created by student Sydney Zink on 2/23/14.
//  Teacher: Hendrix
//  Copyright (c) 2014 Sydney Zink. All rights reserved.
//

// Include the definitions for the CVariable and CVarDB classes in cvariable.h
// Include the member function implementations for
// the CVariable and CVarDB classes in cvariable.cpp.

#include "cvariable.h"

// ----- ----- ----- ----- ----- ----- -----
// cvariable.cpp FILE...
// its better practice to have a separate .h and .cpp file
// for every class you create
// so this doesnt really make sense... but assignment says so
// ----- ----- ----- ----- ----- ----- -----

// attempt at example for virtual functions / base classes
// for example, you can't just create a "Shape" [theoretical class]
// it would store some shared components,
// like the name of the shape or whether it is closed (member variables)
// but you would have Triangle as a subclass of virtual class Shape,
// and make THAT to make a Triangle
// and if you had Square as a subclass, that would still use
// base features from shape (like name, bool isClosed)
// but would implement it differently from triangle


// ----------------------------------------------------------------------------
// 	CVariable class
//
// A class to represent the variables defined by the user
// --> store the name and value of a user-defined variable
//
// (CVarDB will organize and retrieve these variables for Mini-Matlab program)
// ----------------------------------------------------------------------------




// initializes a CVariable - with a given name and value 0
CVariable::CVariable(const char* init_name)
{
    // store the name and value of a user-defined variable
    //char* name;   // char array (char*) to hold the name
    //double value; // double to store the variable value
    
    // is this something you have to do because your prof
    // likes to write in c even though this is a c++ class?
    // my intuition tells me that you can set them directly equal
    // to one another... but maybe since they're const char pointers
    // and not strings like a normal person would use
    // you have to do this jankyness
    
    name = new char(strlen(init_name)+1);
    name = strcpy(name, init_name); // copy name into m_sName
    value = 0;
    
    // YOU ARE OVERUSING "this"
    // this->value = 0;
    
    // you only need to use the "this" keyword if
    // the parameter has the same exact name as the member variable
    // i.e. a param is called "name", and the private member var is also "name"
    // then you would say this.name = name
    // meaning set the "name" of THIS object equal to the "name" parameter value
    
}

// Initializes a CVariable - with a given name and value
CVariable::CVariable(const char* init_name, double init_value)
{
    // name = init_name;
    // again, if assigning your name works, stick with it
    // stupid not using string...
    
    name = new char[strlen(init_name) + 1];
    strcpy(name, init_name);
    value = init_value;
}

// Copy constructor
CVariable::CVariable(const CVariable& copy)
{
    //char* name; //double value;
    
    //CVariable m = copy;
    
    //this->name=new char(strlen(copy.name)+1);
    // this->name isnt necessary, just name
    name = new char(strlen(copy.name)+1);
    // int i=0;
    
    for(int i=0; i<strlen(copy.name)+1; i++) //deep copy
    {
        this->name[i] = copy.name[i];
    }
    //this->name=copy.name;  //shallow copy, wrong
    
    //this->value = copy.value; // stop the this!
    
    value = copy.value; //okay b/c a single value
    
    // just to make sure you understand:
    // shallow copy means it will simply *point* to the same data
    // so if you change the "copy", it will change the original data
    // whereas with a deep copy, you *actually make a duplicate* of the data
    // and changing the copy will NOT change the original data
}

// NOTE: the "BIG 3" are typically defined near each other
// aka the constructor, copy constructor, and destructor

// Destroys the CVariable
CVariable::~CVariable()
{
    // ...muuuahhahaha DESTROY EVERYTHING
    
    // deallocate any memory you gave to these fellas
    //char* name;   // char array (char*) to hold the name
    //double value; // double to store the variable value
}

// Return the name of this CVariable
CVariable::const char* getName() const
{
    return name;
}

// below functions must be implemented by a subclass
// because virtual keyword means they can't be defined by CVariable
// CVariable will be a parent class, sort of like a template
// for something that could actually be instantiated

// can't remember how you define them with CVariable:: in front or what...

// but it is unclear to me what the CVariable subclasses are....??

// Return a reference to the value stored in this CVariable
double& CVariable::operator*()
{
    //return this->Value();
    return value;
    // don't need this, because this is a member function
    // --> so it has access to its private member variable, "value"
    
    // not sure why you called Value() instead of returning value itself
    // since your Value function only consists of {return value;}
}

// Return the value stored in a const CVariable
virtual double operator*() const;

virtual CVariable& CVariable::operator=(double newValue);

// Set the value of this CVariable to match that of the given CVariable
// (returns the CVariable)
virtual CVariable& CVariable::operator=(CVariable& newValue);




// ----------------------------------------------------------------------------
// 	CVarDB class
//
// CVarDB class should store and manage the collection
// of all currently defined variables in a vector.
// The CVarDB shalso manage the "automatic" variable ans.ould
//
// ----------------------------------------------------------------------------


// dont remember what to do with this....
friend ostream& CVarDB::operator<<(ostream& out, CVarDB& cdb)
{
    // implementation...
}

// initializes the variable database to contain only the ans variable
CVarDB::CVarDB()
{
    // vector<CVariable> db;
}

// destroys the DB
CVarDB::~CVarDB()
{
    // delete db vector
}

// ;
//

/* ----------------------------------------------------------------------------
 Name:     add
 Purpose:  adds a new CVariable to the DB
 Params:   newVar
 Returns:  returns false if the variable name is already taken, true otherwise
 ---------------------------------------------------------------------------- */
bool CVarDB::add(CVariable& newVar)
{
    return false;
}

// returns a pointer to the CVariable in the DB with the given name
// or NULL if not found
CVariable* CVarDB::search(const char* name)
{
    return NULL;
}



// these are declared here but defined in the main.cpp file...???


ostream& operator<<(ostream& out, CVariable& cvar);


ostream& operator<<(ostream& out, CVarDB& cdb);


//lezbfriendsss

// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar)
{
    out<<"NAME:"<<cvar.name<<" VALUE:";
    out << cvar.value;
    return out;
}

// prints out every CVariable in the DB
ostream& operator<<(ostream& out, CVarDB& cdb)
{
    
    //cout << cdb;
    //do for loop to go through every element in the database
    for (int i = 0; i < cdb.m_nSize - 1; i++)
    {
        out << "name:" << ((cdb.db).at(i)).getName() << "  value:";
        out << ((cdb.db).at(i)).Value() << endl;
    }
    return out;
}
