// Simple back end for keeping track of the books in a library.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// store all pertinent information about a given book
class Book {
	string title;
	string author;
	string isbn;
	bool available;		// availability for check out
public:
	Book(string title, string author, string isbn, bool available);
	class Invalid {};			// to throw as an exception
	void print();				// print book info
	string get_title() { return title; }
	bool get_available() { return available; }
	void set_available(bool io) { available = io; }
};

// proper ISBN input is of the form  n-n-n-x  where n is an integer and x is an int or a letter
//	ISBNs will be stored as  nnnx.
bool is_isbn(string &isbn) {
	isbn.erase(remove(isbn.begin(), isbn.end(), '-'), isbn.end());
	if (isbn.size() != 4) return false;
	for (int i = 0; i < 3; ++i) {
		if (!isdigit(isbn[i]))
			return false;
	}
	if (!isalnum(isbn[3]))
		return false;
	return true;
}

Book::Book(string ctitle, string cauthor, string cisbn, bool cavailable)
	: title{ ctitle }, author{ cauthor }, isbn{ cisbn }, available{ cavailable }
{
	if (!is_isbn(cisbn)) throw Invalid{};
}


void Book::print() {
	cout << title << " by " << author << endl
		<< "ISBN = " << isbn << endl;
	if (available)
		cout << "Is available." << endl << endl;
	else
		cout << "Is not available." << endl << endl;
}

// /////////////////////////

class Library {
public:
	vector<Book> contents = {};
	int is_book(string title);
};

Library pub_lib;

int Library::is_book(string title) {
	if (contents.size() <= 0) { return -1; }
	for (int i = 0; i < contents.size(); ++i) {
		if (title == contents[i].get_title())
			return i;
		else
			return -1;
	}
}


// check to see if a book can be checked in or checked out, based on value of status
void check_io(string title, string io) {
	int storage_number = pub_lib.is_book(title);
	if (storage_number > -1) {
		Book &query = pub_lib.contents[storage_number];	// create a reference so that we can modify
		if (io == "in") {
			if (query.get_available() == false) {
				query.set_available(true);
				cout << title << " is now checked in." << endl;
			}
			else
				cerr << "Book is already checked in." << endl;
		}
		if (io == "out") {
			if (query.get_available() == true) {
				query.set_available(false);
				cout << title << " is now checked out." << endl;
			}
			else
				cerr << "Book is not available." << endl;
		}
		if (io != "in" && io != "out")
			cerr << "That is not a valid action." << endl;
	}
}

int main()
try {
	while (true) {
		string isbn;
		string title;
		string author;
		cout << "Please enter the book title, author, and isbn." << endl;
		bool entering = true;
		while (entering) {
			cin >> title;
			if (title == "stop")
				entering = false;
			else {
				cin >> author >> isbn;
				Book new_book = Book(title, author, isbn, true);
				pub_lib.contents.push_back(new_book);
			}
		}
		cout << "Enter a title you would like to check out." << endl;
		string io;
		cin >> title >> io;
		check_io(title, io);
		for (int i = 0; i < pub_lib.contents.size(); ++i)
			pub_lib.contents[i].print();
	}
}
catch (Book::Invalid) {
	cerr << "Error: Invalid ISBN." << endl;
}

