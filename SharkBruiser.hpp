///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    SharkBruiser.hpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "PlayerCharacter.hpp"
#include <string>

class SharkBruiser : public PlayerCharacter {
private:
    bool isPlayerControlled;
protected:
    void basicAttack(PlayerCharacter& target) override;
    void bloodBite(PlayerCharacter& target);
public:
    SharkBruiser(std::string& newName, int& raceCode, bool isPlayer = false);
    void performAction(PlayerCharacter& target) override;
};
