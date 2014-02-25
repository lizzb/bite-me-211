// http://pastebin.com/y4SQpmCS
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


    //can't remember how you deal with friends... declaration things
    friend ostream& CVariable::operator<<(ostream& out, CVariable& cvar)
{
    
}

    // initializes a CVariable - with a given name and value 0
    CVariable::CVariable(const char* init_name)
    {
    	// store the name and value of a user-defined variable
        //char* name;   // char array (char*) to hold the name
        //double value; // double to store the variable value
        name = init_name;
        value = 0.0;
    }
    
    // Initializes a CVariable - with a given name and value
    CVariable::CVariable(const char* init_name, double init_value)
    {
        name = init_name;
        value = init_value;
    }
    
    // Copy constructor
    CVariable::CVariable(const CVariable& copy)
    {
        //char* name;
        //double value;
    }
    
    // return the name of this CVariable
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
    
    // return a reference to the value stored in this CVariable
    virtual double& CVariable::operator*();
    
    // return the value stored in a const CVariable
    virtual double operator*() const;
    
    virtual CVariable& CVariable::operator=(double newValue);
    
    // set the value of this CVariable to match that of the given CVariable
    // (returns the CVariable)
    virtual CVariable& CVariable::operator=(CVariable& newValue);
    
    // destroys the CVariable
    virtual CVariable::~CVariable();
    

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

// prints out a CVariable
ostream& operator<<(ostream& out, CVariable& cvar);

// prints out every CVariable in the DB
ostream& operator<<(ostream& out, CVarDB& cdb);
