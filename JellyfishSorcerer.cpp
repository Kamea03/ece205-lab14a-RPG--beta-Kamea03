///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    Jellyfish Sorcerer.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "JellyfishSorcerer.hpp"
#include <iostream>
#include <limits>

JellyfishSorcerer::JellyfishSorcerer(std::string& newName, int& raceCode, bool isPlayer)
    : PlayerCharacter(newName, raceCode), isPlayerControlled(isPlayer) {
    int maxHth = 20; setMaxHealth(maxHth);
    int hth = maxHth; setHealth(hth);
    int str = 8; setStrength(str);
    int def = 1; setDefense(def);
}

void JellyfishSorcerer::basicAttack(PlayerCharacter& target) {
    int damage = getStrength() - target.getDefense();
    if (damage < 1) damage = 1;
    std::cout << getName() << " uses TENTACLE WHIP!" << std::endl;
    target.takeDamage(damage);
}

void JellyfishSorcerer::lightningZap(PlayerCharacter& target) {
    int damage = getStrength() + 5; //magic ignore defense
    std::cout << getName() << " channels Aquarium-235 and uses LIGHTNING ZAP!" << std::endl;
    target.takeDamage(damage);
}

void JellyfishSorcerer::performAction(PlayerCharacter& target) {
    if (isPlayerControlled) {
        int choice;
        std::cout << "Select an ACTION:\n  [0] TENTACLE WHIP (Basic)\n  [1] LIGHTNING ZAP (Magic)\nChoice: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || choice < 0 || choice > 1) {
                std::cin.clear(); std::cin.ignore(10000, '\n');
                std::cout << "Invalid. Enter 0 or 1: ";
            } else break;
        }
        if (choice == 1) lightningZap(target);
        else basicAttack(target);
    } else {
        static int turnCounter = 0; turnCounter++;
        if (turnCounter % 3 == 0) lightningZap(target);
        else basicAttack(target);
    }
}