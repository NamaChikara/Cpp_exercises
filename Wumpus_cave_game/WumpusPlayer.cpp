#include "WumpusPlayer.h"

Player::Player(std::string uname, int loc, int arr)
	: name{ uname }, location{ loc }, arrows{ arr } {}

void Player::get_move(std::vector<int> tunnels) {
	std::string action;
	getline(std::cin, action);
	std::stringstream ss{ action };

	bool valid = false;
	char type;
	ss >> type;
	if (type == 'm') {
		int destination;
		ss >> destination;
		for (int i = 0; i < tunnels.size(); ++i) {
			if (tunnels[i] == destination)
				valid = true;
		}
		if (valid) {
			location = destination;
			return;
		}
		else {
			std::cout << "You cannot move to that room." << std::endl;
			return;
		}
	}
	if (type == 's') {
		char dash;
		int shot;
		std::vector<int> path;
		ss >> shot;
		bool valid = false;
		for (int i = 0; i < tunnels.size(); ++i) {
			if (tunnels[i] == shot)
				valid = true;
		}
		if (valid)
			path.push_back(shot);
		else {
			std::cout << "You cannot shoot to room " << shot << "." << std::endl;
			return;
		}
		while (ss.rdbuf()->in_avail() != 0) {
			valid = false;
			ss >> dash >> shot;
			if (dash != '-') {
				std::cout << "Invalid shot syntax." << std::endl;
				return;
			}
			for (int i = 0; i < tunnels.size(); ++i) {
				if (tunnels[i] == shot)
					valid = true;
			}
			if (valid)
				path.push_back(shot);
			else {
				std::cout << "You cannot shoot to room " << shot << "." << std::endl;
				return;
			}
		}
		shot_path = path;
		arrows -= 1;
		return;
	}
	else {
		std::cout << "Character " << type << " is an invalid action." << std::endl;
		return;
	}
}