# Knights of Pearl: FISH RPG Beta (Lab 14a)

**Author:** Kamea McMillan-Zilberman  
**Co-Author:** Jayden Collado  

## Game Description & Overview
Welcome to **Dasani**, a sprawling aquatic planet home to an estimated 10 trillion highly intelligent sea creatures. This peaceful utopia owes its advanced evolution and technology to **Aquarium-235**, a powerful resource embedded in the planet's land and its inhabitants. 

Recently, humans discovered Dasani and negotiated a treaty to share resources in exchange for the immortality that Aquarium-235 provides. However, rumors are swirling that human mercenaries are secretly kidnapping sea creatures to study them and synthesize artificial Aquarium-235.

You play as a **Knight of Pearl**, a sworn protector of the Grand Barrier Reef. This project features a JSON-driven branching narrative where you must investigate the smuggling ring, leading into a highly strategic, turn-based battle against rogue enemies.

## Objective
Navigate through a branching narrative decision tree to uncover the truth about the human treaty and the missing Aquarium-235. Confront rogue smugglers and survive turn-based combat to protect your planet. The game ends when you either make a fatal story decision or defeat the enemy boss in combat!

## Rules of the Game

### Story Navigation
* **Decision Points:** Read the story prompts carefully. Enter `1` or `2` to make decisions that dictate where you explore (e.g., the Transit Line or the Human Facility). 
* **Dynamic Encounters:** Your choices determine if you catch the enemy, call for backup, or get ambushed.

### Battle Rules
* **Win Condition:** The battle continues looping until a character's HP drops to `0`. The surviving character is declared the winner.
* **Resource Management:** Certain abilities cost class-specific resources (like "Ink Charges"). Players must carefully manage their resources by utilizing basic attacks to recharge them for more powerful abilities.
* **Turn Order:** You will always input your action on your turn, while the enemy utilizes an automatic AI script to fight back.

## Playable Classes & Action Descriptions
At the start of the game, you can choose to play as one of four unique aquatic classes:

**[0] Octopus Assassin (Featured Class)**
* **[0] BASIC ATTACK:** Deals standard physical damage based on your STRENGTH versus the opponent's DEFENSE. Restores 1 INK CHARGE.
* **[1] INK MARK:** Consumes 1 INK CHARGE. Shoots a glob of ink to mark the enemy. The next physical ability used against a marked enemy will have special critical effects and deal bonus damage. Can be used while in stealth.
* **[2] TENTACLE SMACK:** A heavy physical attack. If the enemy is currently MARKED WITH INK, this deals massive critical bonus damage and consumes the mark. If the enemy is not marked, it deals severely reduced damage.
* **[3] INK SHROUD / STAY HIDDEN:** Consumes 1 INK CHARGE. Surrounds the player in a cloud of ink, granting temporary stealth. Being in stealth increases DEFENSE and builds up stealth stacks. For every turn spent hidden, you gain a massive damage bonus on your next attack out of stealth. Stacks up to two times.

**[1] Shark Bruiser**
* A physical powerhouse that relies on high base strength and unleashes massive critical bites every 3rd turn.

**[2] Pufferfish Defender**
* The tank of the group. Boasts the highest health pool and defends with piercing poison spikes.

**[3] Jellyfish Sorcerer**
* Low health, but highly lethal. Channels raw Aquarium-235 for heavy, defense-bypassing magic damage.

(to run: make clean then make run)
