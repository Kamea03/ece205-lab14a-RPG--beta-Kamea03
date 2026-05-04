///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    PufferfishDefender.hpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "PlayerCharacter.hpp"
#include <string>

class PufferfishDefender : public PlayerCharacter {
protected:
    void basicAttack(PlayerCharacter& target) override;
    void spikeSwell(PlayerCharacter& target);
public:
    PufferfishDefender(std::string& newName, int& raceCode);
    void performAction(PlayerCharacter& target) override;
};