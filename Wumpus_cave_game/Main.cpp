// Implementation of the game "Hunt the Wumpus", a non-graphical game
//  where the user can walk between linked rooms and search for the 
//  Wumpus monster.  Each turn, the user is alerted if an adjacent room
//  has a bat, pit, or the Wumpus.  Walking into a bat room causes the 
//	user to be lifted to a random room.  Walking into a pit causes the
//  user to die, same goes for a Wumpus.  
// Instead of moving, the user can shoot an arrow through the linked rooms
//  in an attempt to kill the Wumpus.  If it doesn't kill, the Wumpus 
//  moves rooms.

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>
#include "WumpusCave.h"

int main() {
	std::vector<Room> cave = initialize_cave(100);
	print_stats(cave);
	std::cin.get();
}