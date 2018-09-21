// Defines operations for (country, currency) pairs (i.e. the struct Conversion).

#include "Currency.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
std::vector<Conversion> read_ratios(std::string file) {
	std::ifstream ifs{ file };
	if (!ifs) throw my_error("can't open " + file);
	Conversion c;
	std::vector<Conversion> rates;
	while (ifs >> c)		// read Conversions into rates
		rates.push_back(c);
	return rates;
}

// convert money (n) from initial currency to final currency
double convert_money(double to_convert, std::string initial_c, std::string final_c,
	std::vector<Conversion> ratios)
{
	double initial_ratio = 0;
	double final_ratio = 0;
	// iterate over vector of ratios to find appropriate values
	for (std::vector<int>::size_type i = 0; i != ratios.size(); ++i)
	{
		if (ratios[i].country == initial_c)
			initial_ratio = ratios[i].usd_ratio;
		if (ratios[i].country == final_c)
			final_ratio = ratios[i].usd_ratio;
	}
	if (initial_ratio == 0 && final_ratio == 0)
		throw my_error("Currency types " + initial_c + '\t' + final_c + " not found.");
	double converted = (double)to_convert * (initial_ratio / final_ratio);
	return converted;
}

// return the country names from a vector of Conversions
std::string get_countries(std::vector<Conversion> cons)
{
	std::string names;
	// build the string of names by iterating through cons
	for (std::vector<int>::size_type i = 0; i < cons.size(); ++i) {
		if (i != cons.size() - 1)
			names += cons[i].country + ", ";
		else
			names += cons[i].country + ".";
	}
	return names;
}

// convert from string to double
double str_to_double(std::string s)
{
	std::istringstream is{ s };
	double d;
	is >> d;
	if (!is) my_error("double format error: " + s);
	return d;
}

// convert from double to string
std::string double_to_str(double d)
{
	std::ostringstream os;
	os << d;
	std::string s = os.str().c_str();
	return s;
}