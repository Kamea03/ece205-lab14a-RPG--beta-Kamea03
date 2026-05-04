///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205
//
///
/// @file    GameCharacter.cpp
/// DO NOT MODIFY
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "GameCharacter.hpp"

//Default GameCharacter constructor
GameCharacter::GameCharacter() = default;

//create a game character object with a name
GameCharacter::GameCharacter(std::string& newName){
    GameCharacter::name = newName;
}

//report values of object members
std::string GameCharacter::getName(){
    return name;
}

//update values of object members
void GameCharacter::setName(std::string& newName){
    name = newName;
}

void GameCharacter::greet() const{
    std::cout << name << ": " << "Hello, my name is " << name << "." << std::endl;
}

void GameCharacter::speak(std::string& response){
    std::cout << name << ": " << response << std::endl;
}
