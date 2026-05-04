///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a- RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    PlayerCharacter.hpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameCharacter.hpp"
#include <string>

//inherit from game character publicly
class PlayerCharacter : public GameCharacter {
public:
    // Changed enums to reflect planned game
    enum class Race {
        OCTOPUS = 0,
        SHARK = 1,
        PUFFERFISH = 2,
        JELLYFISH = 3
    };

private:
    Race race;
    int strength;
    int health;
    int agility;
    int defense;

    // Added by Jayden
    int maxHealth;
    int maxResource;
    int resource;

    //rollDice now private
    int rollDice(int upper, int lower);

protected:
    virtual void basicAttack(PlayerCharacter& target);

public:
    //constructer
    PlayerCharacter(std::string& newName, int& raceCode);

    //getters
    Race getRace() const;
    int getStrength() const;
    int getMaxHealth() const;
    int getAgility() const;
    virtual int getDefense() const; // Made virtual by Jayden

    //setters
    void setRace(int& newRaceCode);
    void setStrength(int& newStrength);
    void setHealth(int& newHealth);
    void setAgility(int& newAgility);
    void setDefense(int& newDefense);

    // ADDED BY JAYDEN
    int getResource();
    int getMaxResource();
    void setResource(int& newResource);
    void setMaxResource(int& newMaxResource);
    void setMaxHealth(int& newMaxHealth);
    void addResource(int& addResourceAmount);
    void consumeResource(int& consumeResourceAmount);
    void takeDamage(int damage);

    //print characters stats
    void printStats() const;

    virtual void performAction(PlayerCharacter& target);
};