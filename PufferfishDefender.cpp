///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    PufferfishDefender.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "PufferfishDefender.hpp"
#include <iostream>

PufferfishDefender::PufferfishDefender(std::string& newName, int& raceCode) : PlayerCharacter(newName, raceCode) {
    int maxHth = 40; setMaxHealth(maxHth);
    int hth = maxHth; setHealth(hth);
    int str = 4; setStrength(str);
    int def = 6; setDefense(def);
}

void PufferfishDefender::basicAttack(PlayerCharacter& target) {
    int damage = getStrength() - target.getDefense();
    if (damage < 1) damage = 1;
    std::cout << getName() << " uses TACKLE!" << std::endl;
    target.takeDamage(damage);
}

void PufferfishDefender::spikeSwell(PlayerCharacter& target) {
    int damage = 5; // Fixed piercing damage
    std::cout << getName() << " swells up and uses POISON SPIKES!" << std::endl;
    target.takeDamage(damage);
}

void PufferfishDefender::performAction(PlayerCharacter& target) {
    static int turnCounter = 0;
    turnCounter++;
    if (turnCounter % 2 == 0) spikeSwell(target);
    else basicAttack(target);
}