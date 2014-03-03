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
//     CVariable class
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
    //delete[] name;
    //delete &value;
    
    // deallocate any memory you gave to these fellas
    //char* name;   // char array (char*) to hold the name
    //double value; // double to store the variable value
    // i thought that primitive values (like double) deleted themselves
    // but i might be thinking of java?
    // usually if the "new" keyword is used on something
    // you need to destroy that later
}

// Return the name of this CVariable
char* CVariable::getName() const
{
    return name;
}


// below functions must be implemented by a subclass
// because virtual keyword means they can't be defined by CVariable
// CVariable will be a parent class, sort of like a template
// for something that could actually be instantiated

// can't remember how you define them with CVariable:: in front or what...
// but it is unclear to me what the CVariable subclasses are....??
// but you just went with something so hey i'll go with that


// ONE OF THE 2 BELOW FUNCTIONS NEEDS TO BE CHANGED
// operator* returning a reference vs the actual value


// Return a reference to the value stored in this CVariable
double& CVariable::operator*()
{
    //return this->Value(); // unnecessary this again
    return value; // but you're supposed to return its address, not value...
    
    // don't need this, because this is a member function
    // so it has access to its own private member variable, "value"
    // and it's okay practice to return your OWN member variables
    // getters - like Value(), or as it should be called, getValue() -
    // are usually used by external classes calling it on the object
    // because they DONT have access to the member variable
    
    // not sure why you called Value() instead of returning value itself
    // since your Value function only consists of {return value;}
}

// Return the value stored in a const CVariable
double CVariable::operator*() const
{
    return this->Value();
    // since this function returns the actual value,
    // and the previous one returns a REFERENCE to the value
    // they shouldn't be the same
    // pretty sure this is the one that should return value,
    // and the one above should be edited
}

CVariable& CVariable::operator=(double newValue)
{
    //this->value = newValue; // THE THIS IS TOO MUCH
    value = newValue;
    return *this;
}

// Set the value of this CVariable to match that of the given CVariable
// (returns the CVariable)

// newValue was a misleading name, since its a new CVariable
CVariable& CVariable::operator=(CVariable& otherCVar)
{
    //CVariable tmp(newValue);
    //swap(tmp);
    //this->name = new char(strlen(otherCVar.getName())+1);
    //int i=0;
    //name = new char(strlen(otherCVar.getName())+1);
    //otherName = new char(strlen(otherCVar.getName())+1); // why do you do this
    // wait why are you adding 1 to the length?
    // since indexes start at 0
    // the last index will always be length - 1
    // also you are creating a variable above
    // which i renamed otherName to not mix it up with name, the member variable
    // of THIS CVariable (which will be accessed even without the this keyword
    // also the specs don't say you need to give them the same name
    // but you know better than i
    for(int i=0; i<strlen(otherCVar.getName())+1; i++)  //deep copy
    {
        //this->name[i]=otherCVar.getName()[i];
        name[i] = otherCVar.getName()[i];
    }
    //this->name = newValue.getName();
    //this->value = newValue.Value();
    value = otherCVar.Value();
    return *this;
}




// ----------------------------------------------------------------------------
//  CVarDB class
//
// CVarDB class should store and manage the collection of
// all currently defined variables in a vector.
// The CVarDB shalso manage the "automatic" variable ans.ould
//
// ----------------------------------------------------------------------------




// initializes the variable database to contain only the ans variable
CVarDB::CVarDB()
{
    // vector<CVariable> db;
    CVariable ans("ans", 0);
    db.push_back(ans);
    m_nSize = 1;
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
bool CVarDB::add(CVariable& newVar) //FINISHED AND CORRECT, DO NOT TOUCH // OKAY JEEZ LADY I WON'T
{
    db.push_back(newVar);
    m_nSize++;
    return 1;
}

// returns a pointer to the CVariable in the DB with the given name
// or NULL if not found
CVariable* CVarDB::search(const char* name)
{
    //int f = 0;
    //CVariable* newptr;
    CVariable* newptr = NULL;
    
    // again, why are you subtracting from the size?
    // if the size is 5, the last index will be 4
    // the way you're structuring it
    // you'll only get to max index 3
    // ie not accessing the last element
    // you could do   < m_nSize   OR   <= m_nSize - 1
    // maybe you were trying ot do one of those?
    for (int i = 0; i < m_nSize - 1; i++)
    {
        // i don't know what this is doing?
        // but side note -
        // if something is evaluated to be true within parentheses
        // including == true is redundant
        // though it can help with readability of code
        // so its not bad or anything
        if (strcmp((db.at(i)).getName(), name) == true)
        {
            newptr = &db[i];
            break;
        }
       /* else
        {
            newptr = NULL;
        }
        */
    }
    return newptr; // will return NULL if didn't go into the for loop
}


// thought these should've been defined in the main.cpp file...???
// ostream& operator<<(ostream& out, CVariable& cvar);
// ostream& operator<<(ostream& out, CVarDB& cdb);


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
