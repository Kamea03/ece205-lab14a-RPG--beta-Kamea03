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
#include <limits>

PufferfishDefender::PufferfishDefender(std::string& newName, int& raceCode, bool isPlayer)
    : PlayerCharacter(newName, raceCode), isPlayerControlled(isPlayer) {
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
    if (isPlayerControlled) {
        int choice;
        std::cout << "Select an ACTION:\n  [0] TACKLE (Basic)\n  [1] POISON SPIKES (Piercing)\nChoice: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || choice < 0 || choice > 1) {
                std::cin.clear(); std::cin.ignore(10000, '\n');
                std::cout << "Invalid. Enter 0 or 1: ";
            } else break;
        }
        if (choice == 1) spikeSwell(target);
        else basicAttack(target);
    } else {
        static int turnCounter = 0; turnCounter++;
        if (turnCounter % 2 == 0) spikeSwell(target);
        else basicAttack(target);
    }
}