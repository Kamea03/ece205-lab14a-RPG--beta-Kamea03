///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    OctopusAssassin.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "PlayerCharacter.hpp"
#include <string>

class OctopusAssassin : public PlayerCharacter { // Now inherits directly from PlayerCharacter
private:
    bool isPlayerControlled;
    PlayerCharacter* markedTarget;
    int markBonusDamage;

    // Assassin-specific stealth variables
    bool isStealthed;
    int stealthStacks;
    int stealthDamageBonus;
    int maxStealthStacks;
    int stealthDefenseBonus;

protected:
    void basicAttack(PlayerCharacter &target) override;
    void inkMark(PlayerCharacter& target);
    void tentacleSmack(PlayerCharacter& target);
    void inkShroud();
    void stayStealthed();

public:
    OctopusAssassin(std::string& newName, int& raceCode, bool isPlayer = false);

    void performAction(PlayerCharacter& target) override;
    int getDefense() const override;
};