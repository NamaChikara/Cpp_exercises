// Simple back end for keeping track of the books in a library.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "LibraryTools.h"

//using namespace std;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// ///////////////////////////

LibraryTools::Library pub_lib;

// Initialize pub_lib with some books
LibraryTools::Book b0 = LibraryTools::Book("GrapesOfWrath", "Steinbeck", "123a", true);
LibraryTools::Book b1 = LibraryTools::Book("1Q84", "Murakami", "456b", true);
LibraryTools::Book b2 = LibraryTools::Book("BleakHouse", "Dickens", "789c", true);
LibraryTools::Book b3 = LibraryTools::Book("PaleKing", "DFW", "1111", true);
std::vector<LibraryTools::Book> b = { b0, b1, b2, b3 };

// ///////////////////////////

int main()
try {
	pub_lib.contents = b;
	cout << "Welcome to the public library!" << endl;
	cout << "Would you like to donate any books to our inventory? (y/n)" << endl;
	std::string response;
	cin >> response;
	if (response == "y" || response == "Y")
		pub_lib.process_donation();
	cout << "Would you like to check any books in or out today? (y/n)" << endl;
	cin >> response;
	if (response == "y" || response == "Y")
		pub_lib.check_io();
	cout << "Would you like to see the status of the library contents? (y/n)" << endl;
	cin >> response;
	if (response == "y" || response == "Y") {
		for (int i = 0; i < pub_lib.contents.size(); ++i)
			cout << pub_lib.contents[i] << endl;
	}
	cout << "Thank you for your visit!" << endl;
	return 0;
}
catch (LibraryTools::Book::Invalid) {
	cerr << "Error: Invalid ISBN." << endl;
}