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
#include <json.hpp>

#include "PlayerCharacter.hpp"
#include "Octopus.hpp"
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

    // 1. LOAD DATA
    ifstream file("gameData.json");
    if (!file.is_open()) {
        cerr << "ERROR: Could not open gameData.json!" << endl;
        return 1;
    }
    
    json storyData;
    file >> storyData;
    
    // 2. PARSE CHARACTERS DYNAMICALLY FROM JSON
    std::vector<PlayerCharacter*> combatants;
    auto chars = storyData["characters"];
    for (size_t i = 0; i < chars.size(); ++i) {
        string cName = chars[i]["name"];
        int cRace = chars[i]["raceCode"];

        PlayerCharacter* newChar = nullptr;
        // Map Race Code to specific subclass
        if (cRace == 0) {
            newChar = new OctopusAssassin(cName, cRace);
        } else if (cRace == 1) {
            newChar = new SharkBruiser(cName, cRace);
        } else if (cRace == 2) {
            newChar = new PufferfishDefender(cName, cRace);
        } else if (cRace == 3) {
            newChar = new JellyfishSorcerer(cName, cRace);
        }
        
        if (newChar) combatants.push_back(newChar);
    }

    // 3. STORY LOOP
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

    // 4. BATTLE SEQUENCE
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
            cout << "\n===== Turn: " << turnCounter << " =====\n";
            for (size_t i = 0; i < combatants.size(); ++i) {
                size_t targetIndex = (i + 1) % combatants.size();
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