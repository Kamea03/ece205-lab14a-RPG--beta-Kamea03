///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2025
//
///
/// @file    GameCharacter.hpp
/// DO NOT MODIFY
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

class GameCharacter {

protected:
    std::string name;//Name of Game Character object

public:

    virtual ~GameCharacter() = default;

    //This class offers two constructors:
    GameCharacter(); //This is the default constructor.
    //If a derived class doesn't explicitly call the constructor of its
    //parent class (the base class), the compiler will implicitly call
    //the base class's default constructor (if it exists) before
    //the derived class constructor.

    //
    explicit GameCharacter(std::string& newName); //This is a parameterized constructor.
    //Derived classes usually will not need to explicitly call this type of constructor unless
    //base class initialization is required.

    std::string getName();//Getter: Report the Name of Game Character object

    void setName(std::string& newName);//Setter: Update the Name of Game Character object

    //The greet method will most likely be removed since we also have a speak method that basically
    //does the same thing. However, this provides an example of a simple method that requires no
    //parameters
    virtual void greet() const; //Introduce Self

    //Say canned responses passed in from caller. This method will allow us to control our game
    //characters like puppets. final specifier ensures that it may not be overridden by derived classes.
    virtual void speak(std::string& response) final;
};