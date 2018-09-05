// Simple back end for keeping track of the books in a library.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ///////////////////////////

// store all pertinent information about a given book
class Book {
	string title;
	string author;
	string isbn;
	bool available;		// availability for check out
public:
	Book(string title, string author, string isbn, bool available);
	class Invalid {};			// to throw as an exception
	// Note: without identifying the functions as const members, we cannot pass const Book to 
	//	functions which call get_X().
	string get_title() const { return title; }
	void set_title(string t) { title = t; }
	string get_author() const { return author; }
	void set_author(string a) { author = a; }
	string get_isbn() const { return isbn; }
	void set_isbn(string i) { isbn = i; }
	bool get_available() const { return available; }
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

// construct book if the ISBN is valid
Book::Book(string ctitle, string cauthor, string cisbn, bool cavailable)
	: title{ ctitle }, author{ cauthor }, isbn{ cisbn }, available{ cavailable }
{
	if (!is_isbn(cisbn)) throw Invalid{};
}

// overload << operator so that it is easy to print a book's information
ostream& operator<<(ostream& os, const Book& b)
{
	string status;
	if (!b.get_available()) status = "not ";
	return os << b.get_title() << " by " << b.get_author() << endl
		<< "ISBN = " << b.get_isbn() << endl
		<< "is " << status << "available." << endl;
}

// Books are the same if their ISBN is the same
bool operator==(const Book& a, const Book& b) {
	return a.get_isbn() == b.get_isbn();
}

bool operator!=(const Book& a, const Book& b) {
	return !(a == b);
}

// ///////////////////////////

// create class in which to store books and query the library stock

class Library {
public:
	vector<Book> contents = {};		// to store the books
	int is_book(string title);		// if a title is in contents, returns the index; otherwise returns -1
	bool add_book(Book& b);			// true if b's isbn is not already used by another book in contents
};

int Library::is_book(string title) {
	if (contents.size() <= 0) { return -1; }
	for (int i = 0; i < contents.size(); ++i) {
		if (title == contents[i].get_title())
			return i;
	}
	return -1;
}

bool Library::add_book(Book& b) {
	if (is_book(b.get_title()) == -1) {
		contents.push_back(b);
		return true;
	}
	else
		return false;
}

Library pub_lib;

// ///////////////////////////

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

// ///////////////////////////

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
				if (!pub_lib.add_book(new_book)) cout << "A book with that ISBN already exists." << endl;
			}
		}
		cout << "Enter a title you would like to check out." << endl;
		string io;
		cin >> title >> io;
		check_io(title, io);
		for (int i = 0; i < pub_lib.contents.size(); ++i)
			cout << pub_lib.contents[i];
	}
}
catch (Book::Invalid) {
	cerr << "Error: Invalid ISBN." << endl;
}

