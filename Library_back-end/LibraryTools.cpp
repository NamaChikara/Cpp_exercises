#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "LibraryTools.h"

namespace LibraryTools {

	// proper ISBN input is of the form  n-n-n-x  where n is an integer and x is an int or a letter
	//	ISBNs will be stored as  nnnx.
	bool is_isbn(std::string &isbn) {
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
	LibraryTools::Book::Book(std::string ctitle, std::string cauthor, std::string cisbn, bool cavailable)
		: title{ ctitle }, author{ cauthor }, isbn{ cisbn }, available{ cavailable }
	{
		if (!is_isbn(cisbn)) throw Invalid{};
	}

	// overload << operator so that it is easy to print a book's information
	std::ostream& operator<<(std::ostream& os, const LibraryTools::Book& b)
	{
		std::string status;
		if (!b.get_available()) status = "not ";
		return os << b.get_title() << " by " << b.get_author() << std::endl
			<< "ISBN = " << b.get_isbn() << std::endl
			<< "is " << status << "available." << std::endl;
	}

	// Books are the same if their ISBN is the same
	bool LibraryTools::operator==(const Book& a, const Book& b) {
		return a.get_isbn() == b.get_isbn();
	}

	bool LibraryTools::operator!=(const Book& a, const Book& b) {
		return !(a == b);
	}

	// ///////////////////////////

	// create class in which to store books and query the library stock

	int LibraryTools::Library::is_book(std::string title) {
		if (contents.size() <= 0) { return -1; }
		for (int i = 0; i < contents.size(); ++i) {
			if (title == contents[i].get_title())
				return i;
		}
		return -1;
	}

	// add a book to the library if it doesn't already exist
	bool LibraryTools::Library::add_book(LibraryTools::Book& b) {
		if (is_book(b.get_title()) == -1) {
			contents.push_back(b);
			return true;
		}
		else
			return false;
	}

	// check to see if a book can be checked in or checked out, based on value of status
	void LibraryTools::Library::check_io() {
		std::cout << "Enter a title you would like to check out." << std::endl;
		while (true) {
			std::string title;
			std::cin >> title;
			if (title == "stop")
				return;
			std::string io;
			std::cin >> io;
			int storage_number = is_book(title);
			if (storage_number > -1) {
				LibraryTools::Book &query = contents[storage_number];	// create a reference so that we can modify
				if (io == "in") {
					if (query.get_available() == false) {
						query.set_available(true);
						std::cout << title << " is now checked in." << std::endl;
					}
					else
						std::cerr << title << " is already checked in." << std::endl;
				}
				if (io == "out") {
					if (query.get_available() == true) {
						query.set_available(false);
						std::cout << title << " is now checked out." << std::endl;
					}
					else
						std::cerr << title << " is not available." << std::endl;
				}
				if (io != "in" && io != "out")
					std::cerr << "That is not a valid action." << std::endl;
			}
			std::cout << "Please enter another title, or type 'stop' to exit the checking process." << std::endl;
		}
	}

	// ///////////////////////

	void LibraryTools::Library::process_donation() {
		std::string isbn;
		std::string title;
		std::string author;
		std::cout << "Please enter the book title, author, and isbn." << std::endl;
		bool entering = true;
		while (entering) {
			std::cin >> title;
			if (title == "stop")
				return;
			else {
				std::cin >> author >> isbn;
				LibraryTools::Book new_book = LibraryTools::Book(title, author, isbn, true);
				if (add_book(new_book))
					std::cout << "Thank you for your donation." << std::endl;
				else
					std::cout << "A book with that title already exists." << std::endl;
			}
			std::cout << "Please enter another book, or type 'stop' to exit donation process." << std::endl;
		}
	}

}