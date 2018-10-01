#pragma once

#ifndef Probability_H
#define Probability_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>	// for getting maximum int value

// return a random double between 0 and 1
double get_random();

// return a vector of random doubles between 0 and 1
std::vector<double> get_random(int);

// generate a uniform distribution based on the value of
//  the int argument, and locate the double within it
int get_bucket(int, double);

#endif
