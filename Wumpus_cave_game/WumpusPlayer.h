#pragma once

#ifndef WumpusPlayer_h
#define WumpusPlayer_h

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Player {
public:
	Player(std::string, int = 0, int = 5);
	std::string name;
	int location;
	int arrows;
	std::vector<int> shot_path;
	void get_move(std::vector<int>);
};

#endif