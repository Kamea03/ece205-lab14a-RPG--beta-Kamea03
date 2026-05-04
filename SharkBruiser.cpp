///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    SharkBrusier.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "SharkBruiser.hpp"
#include <iostream>
#include <limits>

SharkBruiser::SharkBruiser(std::string& newName, int& raceCode, bool isPlayer): PlayerCharacter(newName, raceCode), isPlayerControlled(isPlayer) {
    int maxHth = 35; setMaxHealth(maxHth);
    int hth = maxHth; setHealth(hth);
    int str = 7; setStrength(str);
    int def = 3; setDefense(def);
}

void SharkBruiser::basicAttack(PlayerCharacter& target) {
    int damage = getStrength() - target.getDefense();
    if (damage < 1) damage = 1;
    std::cout << getName() << " uses FIN SLAP!" << std::endl;
    target.takeDamage(damage);
}

void SharkBruiser::bloodBite(PlayerCharacter& target) {
    int damage = getStrength() + 3 - target.getDefense();
    if (damage < 1) damage = 1;
    std::cout << getName() << " uses CRITICAL BITE!" << std::endl;
    target.takeDamage(damage);
}

void SharkBruiser::performAction(PlayerCharacter& target) {
    if (isPlayerControlled) {
        int choice;
        std::cout << "Select an ACTION:\n  [0] FIN SLAP (Basic)\n  [1] CRITICAL BITE (Heavy)\nChoice: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || choice < 0 || choice > 1) {
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid. Enter 0 or 1: ";
            } else break;
        }
        if (choice == 1) bloodBite(target);
        else basicAttack(target);
    } else {
        //enemy attack
        static int turnCounter = 0; turnCounter++;
        if (turnCounter % 3 == 0) bloodBite(target);
        else basicAttack(target);
    }
}
}