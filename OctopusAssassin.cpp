///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    OctopusAssassin.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
/// @author  Jayden Collado <jaydenka@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "OctopusAssassin.hpp"
#include <iostream>

// Constructor. Sets to standardized stats
OctopusAssassin::OctopusAssassin(std::string& newName, int& raceCode) : Octopus(newName, raceCode) { // Base Constructor
    int maxHth = 30; setMaxHealth(maxHth);       // +5 MAX HP
    int hth = maxHth; setHealth(hth);
    int str = 6; setStrength(str);               // +1 Str
    int def = 3; setDefense(def);
    int maxRes = 2; setMaxResource(maxRes);
    markBonusDamage = 8;                            // Increased Bonus damage by +4
    int startingInkCharge = 2; setResource(startingInkCharge);

    // Initializes Assassin Octopus specific members
    isStealthed = false;
    stealthStacks = 0;
    maxStealthStacks = 2;
    stealthDamageBonus  = 5;
    stealthDefenseBonus = 2;                    // Temporary measure until agility is implemented;
}

/*  CLASS ABILITY: TENTACLE SMACK ASSASSIN UPGRADE
 *  If target is MARKED WITH INK the opponent takes bonus damage
 *  Reduced damage if no mark present
 *  Exiting stealth or consuming INK MARK deals bonus damage
 */
void OctopusAssassin::tentacleSmack(PlayerCharacter& target) {
    int damage = 0;
    std::cout << "You used TENTACLE SMACK on " << target.getName() << "!";

    // Checks if character is stealthed then adds to damage total
    if ( isStealthed ) {
        damage += (stealthStacks * stealthDamageBonus);
        isStealthed = false;
        stealthStacks = 0;
        std::cout << "You revealed yourself! STEALTH STACKS consumed!";
    }

    // Checks if target isn't marked with Ink. Deals reduced damage otherwise.
    if ( markedTarget != &target ) {
        // If target selected is NOT MARKED WITH INK
        int damagePenalty = 1;
        damage -= damagePenalty;
        std::cout << " It's not as effective without ink...\n" << std::endl;
    }
    else {
        damage += markBonusDamage;
        std::cout << "CRITICAL HIT! ENEMY is no longer MARKED WITH INK!" << std::endl;
        markedTarget = nullptr; // Removes the mark over the opponent;
    }
    damage = damage + getStrength() - target.getDefense();
    target.takeDamage(damage);
}

//
void OctopusAssassin::inkShroud() {
    int spellCost = 1;

    // Spell resource check. Spell fails if not enough Ink Charges
    if ( getResource() < 1 ) {
        std::cout << "INK SHROUD failed! Not enough Ink! Use Basic Attacks to recharge!\n" << std::endl;
        return;
    }

    // Adds a stack of stealth and places unit in Stealth
    isStealthed = true;
    stealthStacks++;
    PlayerCharacter::consumeResource(spellCost);
    std::cout << "You used INK SHROUD! For every turn up to 2 turns in stealth gain +" << stealthDamageBonus << " bonus damage on next BASIC ATTACK or ABILITY!" << std::endl;
    std::cout << "Used " << spellCost <<  " INK CHARGE! You now have " << getResource() << " INK CHARGES!\n" << std::endl;

}

// Allows Octopus to stay in stealth after entering it
void OctopusAssassin::stayStealthed() {
    stealthStacks++;
    if ( stealthStacks > maxStealthStacks ) { stealthStacks = maxStealthStacks; }
    std::cout << "You chose to stay in STEALTH..." << std::endl;
}

// Checks if Octopus is stealthed and adds defensive bonus
int OctopusAssassin::getDefense() const {
    if ( isStealthed ) {
        return (PlayerCharacter::getDefense()  + stealthDefenseBonus);
    }
    return (PlayerCharacter::getDefense());
}

// Basic Attack. Break stealth if you Basic Attack but you still benefit from stealth stacks bonus damage
void OctopusAssassin::basicAttack(PlayerCharacter& target) {
    int damage = 0;

    if (isStealthed) {
        damage += (stealthStacks * stealthDamageBonus);
        isStealthed = false;
        stealthStacks = 0;
        std::cout << "You revealed yourself! STEALTH STACKS consumed!";
    }
    damage = damage + getStrength() - target.getDefense();
    target.takeDamage(damage);
    std::cout << "You used BASIC ATTACK " << "and dealt " << damage << " DAMAGE to " << target.getName() << "!" << std::endl;
    std::cout << "You regained a charge! " << "You now have " << getResource() << " INK CHARGES!\n" << std::endl;

}

// Modifies parent Octopus class to increment stealth stacks
void OctopusAssassin::inkMark(PlayerCharacter& target) {
    if (isStealthed) {
        stealthStacks++;
    }

    int spellCost = 1;

    // Spell resource error checking returns to performAction
    if (PlayerCharacter::getResource() < 1) {
        std::cout << "INK MARK failed! Not enough Ink! Use Basic Attacks to recharge!\n" << std::endl;
        return;
    }

    consumeResource(spellCost); // Consumes Ink charge
    markedTarget = &target;     // Marks target with Ink

    std::cout << "You used INK MARK on " << target.getName() << "! Use another ABILITY on your next turn to deal extra damage!" << std::endl;
    std::cout << "Used " << spellCost <<  " INK CHARGE! You now have " << getResource() << " INK CHARGES!\n" << std::endl;

}

// Perform Action
// Adds functionality for stealth mechanics
void OctopusAssassin::performAction(PlayerCharacter& target) {
    int userInput;

    std::cout << "Select an ACTION: 0 = BASIC ATTACK, 1 = MARK WITH INK, 2 = TENTACLE SMACK, 3 = ";
    if ( isStealthed ) {
        std::cout << "STAY HIDDEN" << std::endl;
    }
    else {
        std::cout << "INK SHROUD" << std::endl;
    }
    while ( true ) {
        std::cin >> userInput;
        switch (userInput) {
            case 0: basicAttack(target); return;
            case 1: inkMark(target); return;
            case 2: tentacleSmack(target); return;
            case 3: if ( isStealthed ) {
                        stayStealthed();
                    } else {
                        inkShroud();
                    } return;

            default: std::cout << "ERROR! Select an ACTION: 0 = BASIC ATTACK, 1 = MARK WITH INK, 2 = TENTACLE SMACK" << std::endl;
        }
    }
}