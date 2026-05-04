///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    OctopusAssassin.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "Octopus.hpp"
#include <string>

class OctopusAssassin : public Octopus {
private:
    bool isStealthed;               // Checks if stealthed flag
    int stealthStacks;              // turn counter to determine stealth stacks
    int stealthDamageBonus;         // stealth bonus damage adds 1 per stack of stealth
    int maxStealthStacks;
    int stealthDefenseBonus;

protected:
    void inkMark(PlayerCharacter& target) override;
    void basicAttack(PlayerCharacter &target) override;
    void tentacleSmack(PlayerCharacter& target) override;
    void inkShroud();
    void stayStealthed();

public:
    OctopusAssassin(std::string& newName, int& raceCode); // Class

    void performAction(PlayerCharacter& target) override;
    int getDefense() const override;

};