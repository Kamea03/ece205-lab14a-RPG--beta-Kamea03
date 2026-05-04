///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    OctopusAssassin.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "OctopusAssassin.hpp"
#include <iostream>
#include <limits>

// Constructor. Initializes all stats and class-specific mechanics directly.
OctopusAssassin::OctopusAssassin(std::string& newName, int& raceCode, bool isPlayer) : PlayerCharacter(newName, raceCode), isPlayerControlled(isPlayer) {
    int maxHth = 30; setMaxHealth(maxHth);
    int hth = maxHth; setHealth(hth);
    int str = 6; setStrength(str);
    int def = 3; setDefense(def);

    int maxRes = 2; setMaxResource(maxRes);
    int startingInkCharge = 2; setResource(startingInkCharge);

    // Ink Mark mechanics
    markedTarget = nullptr;
    markBonusDamage = 8;

    // Stealth mechanics
    isStealthed = false;
    stealthStacks = 0;
    maxStealthStacks = 2;
    stealthDamageBonus = 5;
    stealthDefenseBonus = 2;
}

void OctopusAssassin::basicAttack(PlayerCharacter& target) {
    int damage = getStrength();

    // Add stealth ambush damage if attacking from shadows
    if (isStealthed) {
        std::cout << "\n*AMBUSH BONUS!* ";
        damage += (stealthStacks * stealthDamageBonus);
        isStealthed = false;
        stealthStacks = 0;
    }

    damage -= target.getDefense();
    if (damage < 1) damage = 1;

    std::cout << getName() << " uses BASIC ATTACK!" << std::endl;
    target.takeDamage(damage);

    // Restore 1 INK charge
    int inkGain = 1;
    addResource(inkGain);
    std::cout << "Restored 1 INK CHARGE! (Current: " << getResource() << "/" << getMaxResource() << ")\n" << std::endl;
}

void OctopusAssassin::inkMark(PlayerCharacter& target) {
    int cost = 1;
    if (getResource() < cost) {
        std::cout << "INK MARK failed! Not enough Ink! Use Basic Attacks to recharge.\n" << std::endl;
        return;
    }

    consumeResource(cost);
    markedTarget = &target;

    std::cout << getName() << " used INK MARK on " << target.getName() << "!\nNext physical attack will deal massive critical damage!\n" << std::endl;
}

void OctopusAssassin::tentacleSmack(PlayerCharacter& target) {
    int damage = getStrength();

    std::cout << getName() << " used TENTACLE SMACK!";

    // Check for Ink Mark
    if (markedTarget == &target) {
        damage += markBonusDamage;
        std::cout << " *** CRITICAL HIT ON MARKED TARGET! ***" << std::endl;
        markedTarget = nullptr; // Consume the mark
    } else {
        damage -= 2; // Penalty for using without mark
        std::cout << " (It's not very effective without ink...)" << std::endl;
    }

    // Add stealth ambush damage
    if (isStealthed) {
        std::cout << "*AMBUSH BONUS!* " << std::endl;
        damage += (stealthStacks * stealthDamageBonus);
        isStealthed = false;
        stealthStacks = 0;
    }

    damage -= target.getDefense();
    if (damage < 1) damage = 1;

    target.takeDamage(damage);
}

void OctopusAssassin::inkShroud() {
    int cost = 1;
    if (getResource() < cost) {
        std::cout << "INK SHROUD failed! Not enough Ink!\n" << std::endl;
        return;
    }

    consumeResource(cost);
    isStealthed = true;
    stealthStacks = 1;
    std::cout << getName() << " vanishes into a cloud of ink! Defense increased. Ambush damage charging...\n" << std::endl;
}

void OctopusAssassin::stayStealthed() {
    if (stealthStacks < maxStealthStacks) {
        stealthStacks++;
        std::cout << getName() << " stays hidden in the shadows... Ambush damage is maximizing!\n" << std::endl;
    } else {
        std::cout << getName() << " stays hidden, but ambush damage is already fully charged!\n" << std::endl;
    }
}

// Override getDefense to apply stealth bonus dynamically
int OctopusAssassin::getDefense() const {
    if (isStealthed) {
        return PlayerCharacter::getDefense() + stealthDefenseBonus;
    }
    return PlayerCharacter::getDefense();
}

void OctopusAssassin::performAction(PlayerCharacter& target) {
    if (isPlayerControlled) {
        int userInput;
        std::cout << "INK CHARGES: " << getResource() << "/" << getMaxResource() << std::endl;
        std::cout << "Select an ACTION:\n  [0] BASIC ATTACK\n  [1] INK MARK\n  [2] TENTACLE SMACK\n  [3] ";
        if (isStealthed) std::cout << "STAY HIDDEN\nChoice: ";
        else std::cout << "INK SHROUD\nChoice: ";

        while (true) {
            std::cin >> userInput;
            if (std::cin.fail() || userInput < 0 || userInput > 3) {
                std::cin.clear(); std::cin.ignore(10000, '\n');
                std::cout << "Invalid. Enter 0 to 3: ";
            } else break;
        }
        switch (userInput) {
        case 0: basicAttack(target); return;
        case 1: inkMark(target); return;
        case 2: tentacleSmack(target); return;
        case 3: isStealthed ? stayStealthed() : inkShroud(); return;
        }
    } else {
        // Basic AI for enemy Octopus
        static int turnCounter = 0; turnCounter++;
        if (turnCounter % 3 == 0) tentacleSmack(target);
        else basicAttack(target);
    }
}