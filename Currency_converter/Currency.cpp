#include "Currency.h"
#include <iostream>
#include <vector>
#include <fstream>

Conversion::Conversion(std::string s, double d)
	: country{ s }, usd_ratio{ d } {}

Conversion::Conversion()
	: country{ "" }, usd_ratio{ 0 } {}

void print_conversion(const std::vector<Conversion>& rates) {
	for (Conversion c : rates)
		std::cout << c.country << '\t' << c.usd_ratio << std::endl;
}

// read into a Conversion
std::istream& operator>> (std::istream& ist, Conversion& rate)
{
	// ? add a check on the read in values to make sure country is a 
	//  three letter string
	if (!(ist >> rate.country >> rate.usd_ratio))
		ist.clear(std::ios_base::failbit);
	return ist;
}

// provide an input file stream and use overloaded >> to read Conversions
std::vector<Conversion> read_rates(std::string file) {
	std::ifstream ifs{ file };
	if (!ifs) throw "can't open " + file;
	Conversion c;
	std::vector<Conversion> rates;
	while (ifs >> c)
		rates.push_back(c);
	return rates;
}
