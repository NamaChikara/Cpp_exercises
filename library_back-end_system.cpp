// Simple back end for keeping track of the books in a library.

#include "LibraryTools.h"

//using namespace std;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// ///////////////////////////

LibraryTools::Library pub_lib;

// ///////////////////////////

int main()
try {
	while (true) {
		std::string isbn;
		std::string title;
		std::string author;
		cout << "Please enter the book title, author, and isbn." << endl;
		bool entering = true;
		while (entering) {
			cin >> title;
			if (title == "stop")
				entering = false;
			else {
				cin >> author >> isbn;
				LibraryTools::Book new_book = LibraryTools::Book(title, author, isbn, true);
				if (!pub_lib.add_book(new_book)) cout << "A book with that ISBN already exists." << endl;
			}
		}
		cout << "Enter a title you would like to check out." << endl;
		std::string io;
		cin >> title >> io;
		check_io(pub_lib, title, io);
		for (int i = 0; i < pub_lib.contents.size(); ++i)
			cout << pub_lib.contents[i];
	}
}
catch (LibraryTools::Book::Invalid) {
	cerr << "Error: Invalid ISBN." << endl;
}

