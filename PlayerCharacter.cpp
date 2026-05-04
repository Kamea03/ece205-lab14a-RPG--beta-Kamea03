///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    PlayerCharacter.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <random>
#include "PlayerCharacter.hpp"

using namespace std;

//rollDice as class method
int PlayerCharacter::rollDice(int upper, int lower) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

//constructor
//initializer list to call the GameCharacter base constructor
PlayerCharacter::PlayerCharacter(std::string& newName, int& raceCode) : GameCharacter(newName) {
    health = 100;

    //roll initial stats
    strength = rollDice(10, 0);
    agility = rollDice(10, 0);
    defense = rollDice(10, 0);

    setRace(raceCode);
}

//getters
PlayerCharacter::Race PlayerCharacter::getRace() const { return race; }
int PlayerCharacter::getStrength() const { return strength; }
int PlayerCharacter::getHealth() const { return health; }
int PlayerCharacter::getAgility() const { return agility; }
int PlayerCharacter::getDefense() const { return defense; }

//setters
void PlayerCharacter::setStrength(int& newStrength) { strength = newStrength; }
void PlayerCharacter::setHealth(int& newHealth) { health = newHealth; }
void PlayerCharacter::setAgility(int& newAgility) { agility = newAgility; }
void PlayerCharacter::setDefense(int& newDefense) { defense = newDefense; }

// Modified enum to match species
void PlayerCharacter::setRace(int& newRaceCode) {
    switch (newRaceCode) {
        case 0: race = Race::OCTOPUS; break;
        case 1: race = Race::SHARK; break;
        case 2: race = Race::PUFFERFISH; break;
        case 3: race = Race::JELLYFISH; break;
        default:
            cout << "Invalid Value! Defaulting to Human." << endl;
            race = Race::OCTOPUS;
            break;
    }
}

//print stats method
// Modified to change enums to match species
void PlayerCharacter::printStats() const {
    cout << "\n---------- Stats for " << name << " ----------" << endl;
    cout << "Race: ";

    switch (race) {
        case Race::OCTOPUS: cout << "OCTOPUS" << endl; break;
        case Race::SHARK: cout << "SHARK" << endl; break;
        case Race::PUFFERFISH: cout << "PUFFERFISH" << endl; break;
        case Race::JELLYFISH: cout << "JELLYFISH" << endl; break;
    }

    cout << "Health: " << health << endl;
    cout << "Strength: " << strength << endl;
    cout << "Agility: " << agility << endl;
    cout << "Defense: " << defense << endl;
    cout << "-----------------------------------\n" << endl;

}

// Modified by Jayden beyond here
// Corrected syntax error in performAction()
void PlayerCharacter::performAction(PlayerCharacter&) {
    cout << "I'm sorry, there's nothing I can do." << endl;
}

int PlayerCharacter::getMaxResource() {return maxResource;}
int PlayerCharacter::getResource() {return resource;}

void PlayerCharacter::setResource(int& newResource) { resource = newResource; }
void PlayerCharacter::setMaxResource(int& newMaxResource) { maxResource = newMaxResource; }
void PlayerCharacter::setMaxHealth(int& newMaxHealth) { maxHealth = newMaxHealth; }

void PlayerCharacter::addResource(int& addResourceAmount) {
	resource += addResourceAmount;
	if (resource > maxResource) {
		resource = maxResource;
	}
}

// Subtracts or uses up "spell-casting" resource
void PlayerCharacter::consumeResource(int& consumeResourceAmount) {
	resource -= consumeResourceAmount;
	}

void PlayerCharacter::takeDamage(int damage) {
    if (damage <= 1) {damage = 1;}
    cout << getName() << " took " << damage << " DAMAGE!\n" << endl;
	health -= damage;
	if (health <= 0) {health = 0;}
}

// Simple basic attack using self strength vs target's defense
void PlayerCharacter::basicAttack(PlayerCharacter& target) {
	int damage = getStrength() - target.getDefense();
    target.takeDamage(damage);
}

int PlayerCharacter::getMaxHealth() const {
    return maxHealth;
}