#include "Currency.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
	std::string conversion_file = "currencies.txt";
	std::vector<Conversion> rates = read_rates("currencies.txt");
	print_conversion(rates);
}