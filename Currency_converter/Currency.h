// Creates storage and operations for (country, currency) pairs.

#pragma once

#ifndef Currency_H
#define Currency_H

#include <string>
#include <vector>

// Stores country name and currency value relative to USD
struct Conversion {
	Conversion(std::string, double);
	Conversion();
	std::string country;
	double usd_ratio;
};

void print_conversion(const std::vector<Conversion>&);

// read into a Conversion
std::istream& operator>> (std::istream&, Conversion&);

// provide an input file stream and use overloaded >> to read Conversions
std::vector<Conversion> read_ratios(std::string);

// convert money from initial currency to final currency using conversions
double convert_money(double, std::string, std::string, std::vector<Conversion>);

// get the country names from a vector of Conversions
std::string get_countries(std::vector<Conversion>);

// convert from string to double
double str_to_double(std::string);

// convert from double to string
std::string double_to_str(double);

// error handling
struct my_error : public std::exception
{
	std::string s;
	my_error(std::string ss) : s{ ss } {}
	~my_error() throw() {}
	const char* what() const throw() { return s.c_str(); }
};

#endif 