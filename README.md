# École 42 - Zappy
*Work in progress*
### Overview
Zappy is a project from the IT school École 42 course. The goal is to programm a C game server, an AI that can survive and evolve in its world and a graphical client to see what's happening down there.

The world is a spherical map divided in blocks according to given numbers X and Y.
Each block contains randomly generated food and stones.

To evolve, the AI needs to gather a specified amount of different stones (which differs according to its level) and to be with other AIs.
The AI can perform multiple actions like :
* pick up food,
* drop food,
* eat,
* emit data which can be interpreted by other AIs through the map,
* lay an egg to allow another client to connect,
* evolve

Every action takes a certains time to execute.

The "AI team" that manages to get all its members to the max level wins the game.

### Notions
* Networking,
* Algorithmics,
* Graphics,
* Team work

*Note: This project was developed on OSX.*
