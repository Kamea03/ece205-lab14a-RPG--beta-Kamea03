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

JellyfishSorcerer::JellyfishSorcerer(std::string& newName, int& raceCode) : PlayerCharacter(newName, raceCode) {
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
    int damage = getStrength() + 5; // Magic ignores defense
    std::cout << getName() << " channels Aquarium-235 and uses LIGHTNING ZAP!" << std::endl;
    target.takeDamage(damage);
}

void JellyfishSorcerer::performAction(PlayerCharacter& target) {
    static int turnCounter = 0;
    turnCounter++;
    if (turnCounter % 3 == 0) lightningZap(target);
    else basicAttack(target);
}