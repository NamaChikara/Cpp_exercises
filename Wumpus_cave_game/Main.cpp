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
	std::cout << "Thank you for playing 'Hunt the Wumpus'! \n"
		" Your goal is to move about the cave and determine where the Wumpus is"
		" so that you can kill it. Each turn you will be told which rooms you travel"
		" to, and you will be given hints about whether a pit, bat, or the Wumpus,"
		" is in an adjoining room. \n"
		" 'I feel a breeze' means a pit is nearby; 'I hear a flapping' means a bat is"
		" nearby; 'I smell a Wumpus' means the Wumpus is nearby. \n"
		" If you walk into a room with a pit, you die.  If you walk into a room with"
		" a bat, the bat will move you to a random room. If you walk into a room with"
		" the Wumpus, you die. \n"
		" You are armed with a bow and arrow and can shoot through adjoining rooms"
		" instead of moving.  If the Wumpus is in a room that you shoot through, you"
		" win the game.  If it is not, it moves to a different room (possibly yours!)"
		" You have a limited number of arrows, though. \n"
		" To move to a linked room numbered X, type 'mX'.  To shoot an arrow through"
		" linked rooms X, Y, and Z, type 'sX-Y-Z'. \n"
		" Would you like to play easy (E), medium (M), or hard (H)? \n";
	char mode;
	std::cin >> mode;
	std::cin.ignore(1000, '\n');

	std::vector<Room> cave;
	if (mode == 'E')
		cave = initialize_cave(10, 0.1, 0.2);
	else if (mode == 'M')
		cave = initialize_cave(25, 0.15, 0.3);
	else if (mode == 'H')
		cave = initialize_cave(50, 0.2, 0.4);
	else
		cave = initialize_cave(25, 0.15, 0.3);

	Player user{ "User" };

	bool playing = true;
	while (playing) {
		cave[user.location].print_info();
		give_warning(cave[user.location], cave);
		user.get_move(cave[user.location].links);
		if (user.shot_path.size() != 0) {
			// return true if the wumpus is in the user's shot_path
			if (take_shot(cave, user.shot_path))
				playing = false;
			else
				move_wumpus(cave);
			user.shot_path.clear();
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