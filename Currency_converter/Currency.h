#pragma once

#ifndef Currency_H
#define Currency_H

#include <string>
#include <vector>

// Stores country name and currency value relative to USD
struct Conversion {
	Conversion(std::string s, double d);
	Conversion();
	std::string country;
	double usd_ratio;
};

void print_conversion(const std::vector<Conversion>& rates);

// read into a Conversion
std::istream& operator>> (std::istream& ist, Conversion& rate);

// provide an input file stream and use overloaded >> to read Conversions
std::vector<Conversion> read_rates(std::string file);

#endif 