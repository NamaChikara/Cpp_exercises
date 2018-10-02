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
#include "WumpusPlayer.h"

int main() {
	std::vector<Room> cave = initialize_cave(5);
	print_stats(cave);
	bool wumpus = true;
	Player user{ "Zack" };

	while (wumpus) {
		cave[user.location].print_info();
		user.get_move(cave[user.location].links);
		if (user.shot_path.size() != 0) {
			if (take_shot(cave, user.shot_path))
				wumpus = false;
			user.shot_path.clear();
		}
		else
			give_warning(cave[user.location], cave);
	}
}