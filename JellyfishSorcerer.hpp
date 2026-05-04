///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    JelyfishSorcerer.hpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "PlayerCharacter.hpp"
#include <string>

class JellyfishSorcerer : public PlayerCharacter {
private:
    bool isPlayerControlled;
protected:
    void basicAttack(PlayerCharacter& target) override;
    void lightningZap(PlayerCharacter& target);
public:
    JellyfishSorcerer(std::string& newName, int& raceCode, bool isPlayer = false);
    void performAction(PlayerCharacter& target) override;
};