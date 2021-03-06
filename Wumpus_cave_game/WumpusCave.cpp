#include "WumpusCave.h"
#include "Probability.h"

Room::Room()
	: pit(false), bat(false), wumpus(false), loc(-1) {}

Room::Room(bool p, bool b, bool w, int n, std::vector<int> lnk)
	: pit(p), bat(b), wumpus(w), loc(n), links(lnk) {}

std::vector<Room> initialize_cave(int rooms, double pit_dist, double bat_dist) {
	std::vector<Room> cave(rooms);

	// set location and check if pit or bat should be true via a uniform distribution
	//  the probabiity distribution is [0,pit_dist) U [pit_dist, pit_dist + bat_dist) U [pit_dist + bat_dist, 1]
	//	to ensure only one of pit or bat is selected.

	std::vector<double> probs = get_random(rooms);	// the random values for selecting pit or bat

	for (int i = 0; i < rooms; ++i) {
		cave[i].loc = i;
		if (i != 0) {
			if (probs[i] < pit_dist)
				cave[i].pit = true;
			if (pit_dist <= probs[i] && probs[i] < pit_dist + bat_dist)
				cave[i].bat = true;
		}
	}

	// pick a room for the wumpus (excluding room 0)
	double wump = get_random();
	int wump_room = get_bucket(rooms - 1, wump) + 1;
	cave[wump_room].wumpus = true;

	// determine which rooms are linked
	std::vector<double> link_prob;
	bool repeat = false;	// keep track of if a link already exists
	for (int i = 0; i < rooms; ++i) {
		// first, see if linked to 1, 2, or 3 rooms by using a uniform distribution
		double d = get_random();
		if (d < 1.0 / 3.0)
			link_prob = get_random(1);
		else if (1.0 / 3.0 <= d && d < 2.0 / 3.0)
			link_prob = get_random(2);
		else
			link_prob = get_random(3);
		// next, randomly determine which rooms to link to using 
		//	get_bucket from Probability.h
		for (size_t j = 0; j < link_prob.size(); ++j) {
			int n = get_bucket(rooms, link_prob[j]);
			// check that the link isn't redundant
			if (n == i) 									// a room can't link to itself
				repeat = true;
			for (int k = 0; k < cave[i].links.size(); ++k) {
				if (n == cave[i].links[k])
					repeat = true;
			}
			if (repeat == true) {
				link_prob[j] = get_random();				// reset the link_prob value and try again
				--j;
				repeat = false;
			}
			else
				cave[i].links.push_back(n);
		}
	}
	return cave;
}

void print_room(const Room& r) {
	std::string pit = (r.pit) ? "true" : "false";
	std::string bat = (r.bat) ? "true" : "false";
	std::string wump = (r.wumpus) ? "true" : "false";
	std::cout << "Room number " << r.loc << " has the state " << std::endl;
	std::cout << '\t' << "pit = " << pit << ", bat = " << bat
		<< ", wumpus = " << wump << std::endl;
	std::cout << '\t' << "linked to: ";
	for (size_t i = 0; i < r.links.size(); ++i)
		std::cout << r.links[i] << ", ";
	std::cout << std::endl;
}

void print_stats(const std::vector<Room>& vr) {
	int pit_count = 0;
	int bat_count = 0;
	int wumpus_location = 0;
	double num_linked = 0;
	for (size_t i = 0; i < vr.size(); ++i) {
		if (vr[i].pit)
			++pit_count;
		if (vr[i].bat)
			++bat_count;
		if (vr[i].wumpus)
			wumpus_location = i;
		num_linked += vr[i].links.size();
	}
	double avg_linkage = num_linked / vr.size();
	std::cout << "This cave has " << pit_count << " pits and "
		<< bat_count << " bats. \n The wumpus is in Room "
		<< wumpus_location << ". \n The average number of links is "
		<< avg_linkage << ".\n";
}

void Room::print_info() {
	std::ostringstream os;
	for (int i = 0; i < links.size(); ++i) {
		if (i == links.size() - 1)
			os << links[i];
		else
			os << links[i] << ", ";
	}
	std::string tunnels = os.str();
	std::cout << "You are in room " << loc;
	if (links.size() == 1)
		std::cout << "; there is a tunnel to room ";
	else
		std::cout << "; there are tunnels to rooms ";
	std::cout << tunnels << "; move or shoot?" << std::endl;
}

bool take_shot(const std::vector<Room>& cave, const std::vector<int>& path) {
	for (int i = 0; i < path.size(); ++i) {
		if (cave[path[i]].wumpus == true) {
			std::cout << "You hit the Wumpus in Room " << path[i] << "." << std::endl;
			return true;
		}
	}
	std::cout << "You did not hit the Wumpus." << std::endl;
	return false;
}

void give_warning(const Room& location, const std::vector<Room>& cave) {
	bool is_pit = false;
	bool is_bat = false;
	bool is_wumpus = false;
	for (int i = 0; i < location.links.size(); ++i) {
		if (cave[location.links[i]].pit)
			is_pit = true;
		if (cave[location.links[i]].bat)
			is_bat = true;
		if (cave[location.links[i]].wumpus)
			is_wumpus = true;
	}
	if (is_pit)
		std::cout << "I feel a breeze." << std::endl;
	if (is_bat)
		std::cout << "I hear a flapping." << std::endl;
	if (is_wumpus)
		std::cout << "I smell a Wumpus." << std::endl;
	return;
}

void move_wumpus(std::vector<Room>& cave) {
	int wump_loc = -1;
	for (int i = 0; i < cave.size(); ++i)
		if (cave[i].wumpus == i)
			wump_loc = i;
	int link_number = get_bucket(cave[wump_loc].links.size(), get_random());
	int new_loc = cave[wump_loc].links[link_number];
	cave[wump_loc].wumpus = false;
	cave[new_loc].wumpus = true;
	cave[new_loc].bat = false;	// Wumpus supercedes pre-existing dangers
	cave[new_loc].pit = false;
}