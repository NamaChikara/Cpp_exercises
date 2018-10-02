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
#include "Probability.h"

int main() {
	std::vector<Room> cave = initialize_cave(5);
	print_stats(cave);
	bool playing = true;
	Player user{ "Zack" };

	while (playing) {
		cave[user.location].print_info();
		give_warning(cave[user.location], cave);
		user.get_move(cave[user.location].links);
		if (user.shot_path.size() != 0) {
			if (take_shot(cave, user.shot_path))
				playing = false;
			user.shot_path.clear();
			move_wumpus(cave);
		}
		if (cave[user.location].bat) {
			user.location = get_bucket(5, get_random());
			std::cout << "A bat has dropped you in room " << user.location << "." << std::endl;
		}
		if (cave[user.location].wumpus == true) {
			std::cout << "You moved to the same room as the Wumpus and died." << std::endl;
			playing = false;
		}
		if (cave[user.location].pit) {
			std::cout << "You moved to the same room as a pit and died." << std::endl;
			playing = false;
		}
	}
	std::cin.get();
}