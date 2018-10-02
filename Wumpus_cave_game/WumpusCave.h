#pragma once

#ifndef WumpusCave_H
#define WumpusCave_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Each room may have a pit, bat, or wumpus (not multiple). 
//	Each room has passages to the room numbers in "links" (1, 2, or 3 rooms).
class Room {
public:
	Room();
	Room(bool, bool, bool, int, std::vector<int>);
	void print_info();
	bool pit;
	bool bat;
	bool wumpus;
	int loc;
	std::vector<int> links;
};

// The argument specifies how many rooms to generate.  Only
//  one room will have the wumpus; pit and bat status is determined
//	via probability distributions in Probability.h
std::vector<Room> initialize_cave(int);

// Print to console the status of pit, bat, wumpus, and links.
void print_room(Room);

// Count the number of rooms which have pit, bat, cave, and report
//	the location of the wumpus.
void print_stats(std::vector<Room>);

// Check if the Wumpus is in a room in the vector<int> argument.
bool take_shot(std::vector<Room>, std::vector<int>);

// Report if there is a bat, pit, or wumpus nearby the Room.
void give_warning(Room, std::vector<Room>);

#endif 
