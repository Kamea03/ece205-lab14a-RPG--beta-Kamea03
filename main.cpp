///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - RPG Beta - ECE 205 - Spring 2026
//
///
/// @file    main.cpp
/// @author  Kamea McMillan-Zilberman <kameamz@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>
#include <vector>
#include <string>
#include "json.hpp" // External library

#include "PlayerCharacter.hpp"
#include "OctopusAssassin.hpp"
#include "SharkBruiser.hpp"
#include "PufferfishDefender.hpp"
#include "JellyfishSorcerer.hpp"

using json = nlohmann::json;
using namespace std;

const int delay = 800;

int main() {
    cout << "========================================\n";
    cout << "   Knights of Pearl - FISH RPG Beta     \n";
    cout << "========================================\n\n";

    // --- 1. INFORMATIONAL BLOCK & CLASS SELECTION ---
    cout << "--- CLASS INFORMATION ---\n";
    cout << "[0] Octopus Assassin  : High damage, stealth abilities, relies on ink charges.\n";
    cout << "[1] Shark Bruiser     : High physical stats, lands massive critical bites every 3rd turn.\n";
    cout << "[2] Pufferfish Defender: Highest health, defends with piercing poison spikes.\n";
    cout << "[3] Jellyfish Sorcerer : Low health, but channels Aquarium-235 for heavy magic damage.\n";
    cout << "-------------------------\n\n";

    string playerName;
    int playerClassChoice;

    cout << "Enter your Knight's name: ";
    cin >> playerName;

    cout << "Select your class (0-3): ";
    while (true) {
        cin >> playerClassChoice;
        if (cin.fail() || playerClassChoice < 0 || playerClassChoice > 3) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 0 and 3: ";
        } else {
            break;
        }
    }

    // --- 2. LOAD DATA ---
    ifstream file("gameData.json");
    if (!file.is_open()) {
        cerr << "ERROR: Could not open gameData.json! Make sure it is in the same folder." << endl;
        return 1;
    }

    json storyData;
    file >> storyData;

    // --- 3. PARSE CHARACTERS DYNAMICALLY ---
    std::vector<PlayerCharacter*> combatants;

    // Instantiate Player Character based on user's choice
    PlayerCharacter* player = nullptr;
    if (playerClassChoice == 0) player = new OctopusAssassin(playerName, playerClassChoice);
    else if (playerClassChoice == 1) player = new SharkBruiser(playerName, playerClassChoice);
    else if (playerClassChoice == 2) player = new PufferfishDefender(playerName, playerClassChoice);
    else if (playerClassChoice == 3) player = new JellyfishSorcerer(playerName, playerClassChoice);

    combatants.push_back(player);

    // Read enemies from JSON (We skip index 0 since we manually created the player)
    auto chars = storyData["characters"];
    for (size_t i = 1; i < chars.size(); ++i) {
        string cName = chars[i]["name"];
        int cRace = chars[i]["raceCode"];

        PlayerCharacter* newChar = nullptr;
        if (cRace == 0) newChar = new OctopusAssassin(cName, cRace);
        else if (cRace == 1) newChar = new SharkBruiser(cName, cRace);
        else if (cRace == 2) newChar = new PufferfishDefender(cName, cRace);
        else if (cRace == 3) newChar = new JellyfishSorcerer(cName, cRace);

        if (newChar) combatants.push_back(newChar);
    }

    // --- 4. STORY LOOP ---
    cout << "\nLoading world of Dasani...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    string currentNode = storyData["start"].get<string>();
    bool initiateBattle = false;

    while (true) {
        cout << "\n-------------------------------------------------\n";
        cout << storyData[currentNode]["setting"].get<string>() << "\n\n";

        if (storyData[currentNode].contains("triggerBattle") && storyData[currentNode]["triggerBattle"].get<int>() == 1) {
            initiateBattle = true;
            break;
        }

        if (!storyData[currentNode].contains("option1")) {
            cout << "\nThank you for playing Knights of Pearl!\n";
            return 0;
        }

        int choice;
        cout << "Make your choice (1 or 2): ";
        cin >> choice;

        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        } else {
            if (choice == 1) currentNode = storyData[currentNode]["option1"].get<string>();
            else if (choice == 2) currentNode = storyData[currentNode]["option2"].get<string>();
        }
    }

    // --- 5. BATTLE SEQUENCE ---
    if (initiateBattle && combatants.size() >= 2) {
        cout << "\n=================================================";
        cout << "\n               PREPARE FOR BATTLE!               ";
        cout << "\n=================================================\n\n";

        for (size_t i = 0; i < combatants.size(); ++i) {
            combatants[i]->printStats();
        }

        int turnCounter = 1;
        bool battleOver = false;

        while (!battleOver) {
            cout << "\n=================================================";
            cout << "\n                   TURN " << turnCounter << "                   ";
            cout << "\n=================================================\n";

            // TURN-BY-TURN HEALTH DISPLAY
            cout << "--- CURRENT HEALTH ---\n";
            for (size_t k = 0; k < combatants.size(); ++k) {
                if (combatants[k]->getHealth() > 0) {
                    cout << "> " << combatants[k]->getName() << " HP: " << combatants[k]->getHealth() << "\n";
                }
            }
            cout << "----------------------\n";

            for (size_t i = 0; i < combatants.size(); ++i) {
                size_t targetIndex = (i + 1) % combatants.size();

                // Skip dead combatants
                if (combatants[i]->getHealth() <= 0) continue;

                cout << "\n--- " << combatants[i]->getName() << "'s Turn ---" << endl;
                combatants[i]->performAction(*combatants[targetIndex]);
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));

                if (combatants[targetIndex]->getHealth() <= 0) {
                    cout << "\n*** " << combatants[targetIndex]->getName() << " was defeated! ***" << endl;
                    cout << "*** " << combatants[i]->getName() << " WINS THE BATTLE! ***\n" << endl;
                    battleOver = true;
                    break;
                }
            }
            turnCounter++;
        }
    }

    // Free memory
    for (size_t i = 0; i < combatants.size(); ++i) {
        delete combatants[i];
    }
    combatants.clear();

    return 0;
}