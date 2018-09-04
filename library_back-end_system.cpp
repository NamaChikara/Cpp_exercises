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
	bool available = false;		// availability for check out
public:
	Book(string title, string author, string isbn, bool available);
	class Invalid {};			// to throw as an exception
	void check(string status);	// check if a book is available
	void print();				// print book info
};

vector<Book> library;

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

void Book::print() {
	cout << title << " by " << author << endl
		<< "ISBN = " << isbn << endl;
}

// check to see if a book can be checked in or checked out, based on value of status
void Book::check(string status) {
	if (status == "in") {
		if (available == false)
			available = true;
		else
			cerr << "Book is already checked in." << endl;
	}
	if (status == "out") {
		if (available == true)
			available = false;
		else
			cerr << "Book is not available." << endl;
	}
	if (status != "in" && status != "out")
		cerr << "That is not a valid action." << endl;
}

Book::Book(string ctitle, string cauthor, string cisbn, bool cavailable)
	: title{ ctitle }, author{ cauthor }, isbn{ cisbn }, available{ cavailable }
{
	if (!is_isbn(cisbn)) throw Invalid{};
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
				library.push_back(new_book);
			}
		}
		for (size_t i = 0; i < library.size(); ++i) {
			library[i].print();
		}
	}
}
catch (Book::Invalid) {
	cerr << "Error: Invalid ISBN." << endl;
}
