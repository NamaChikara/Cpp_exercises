#include "Probability.h"

double get_random() {
	std::random_device rd;		// a uniformly-distributed integer random number generator
	std::mt19937 g(rd());		// mt19937 is a type of the mersenne_twister_engine (a random number generator)
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	double rand = dis(g);
	return rand;
}

std::vector<double> get_random(int n) {
	std::vector<double> randoms;
	std::random_device rd;		// a uniformly-distributed integer random number generator
	std::mt19937 g(rd());		// mt19937 is a type of the mersenne_twister_engine (a random number generator)
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	for (int i = 0; i < n; ++i)
		randoms.push_back(dis(g));
	return randoms;
}

int get_bucket(int n, double prob) {
	double dn = n;
	for (int i = 0; i < n; ++i) {
		// determine the endpoints of the interval
		double lower = i / dn;
		double higher = (i + 1.0) / dn;
		// check to see if the value lies in the interval
		if (lower <= prob && prob < higher)
			return (int)i;
	}
	// rare case that prob is not in the set [0, 1).
	if (prob == 1)
		return n;
	return -1;	// error in locating prob within the distribution
}