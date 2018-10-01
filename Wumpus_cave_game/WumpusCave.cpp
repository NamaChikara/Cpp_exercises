#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/sec3_chpt18/sec3_chpt18_exercise12/sec3_chpt18_exercise12/WumpusCave.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/sec3_chpt18/sec3_chpt18_exercise12/sec3_chpt18_exercise12/Probability.h"

Room::Room()
	: pit(false), bat(false), wumpus(false), loc(-1) {}

Room::Room(bool p, bool b, bool w, int n, std::vector<int> lnk)
	: pit(p), bat(b), wumpus(w), loc(n), links(lnk) {}

std::vector<Room> initialize_cave(int rooms) {
	std::vector<Room> cave(rooms);

	// set location and check if pit or bat should be true via a uniform distribution
	//  the probabiity distribution is [0,pit_dist) U [pit_dist, 0.5) U [0.5, bat_dist) U [bat_dist,1]
	//	to ensure only one of pit or bat is selected.
	double pit_dist = 0.1;
	double bat_dist = 0.6;
	std::vector<double> probs = get_random(rooms);	// the random values for selecting pit or bat

	for (int i = 0; i < rooms; ++i) {
		cave[i].loc = i;
		if (probs[i] < pit_dist)
			cave[i].pit = true;
		if (0.5 <= probs[i] && probs[i] < bat_dist)
			cave[i].bat = true;
	}

	// pick a room for the wumpus (excluding the first room)
	double wump = get_random();
	int wump_room = get_bucket(rooms - 1, wump) + 1;
	cave[wump_room].wumpus = true;

	// determine which rooms are linked
	std::vector<double> link_prob;
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
			int n = get_bucket(rooms, link_prob[j]);	// n is between 0 and rooms - 1, add 1 to it
			if (n + 1 == i) {	// a room can't link to itself
				link_prob[j] = get_random();	// reset the link_prob value and try again
				--j;
			}
			else
				cave[i].links.push_back(n + 1);
		}
	}
	return cave;
}

void print_room(Room r) {
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

void print_stats(std::vector<Room> vr) {
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