#pragma once

#ifndef LibraryTools_H
#define LibraryTools_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace LibraryTools {

	// store all pertinent information about a given book
	class Book {
		std::string title;
		std::string author;
		std::string isbn;
		bool available;		// availability for check out
	public:
		Book(std::string title, std::string author, std::string isbn, bool available);
		class Invalid {};			// to throw as an exception
		// Note: without identifying the functions as const members, we cannot pass const Book to 
		//	functions which call get_X().
		std::string get_title() const { return title; }
		void set_title(std::string t) { title = t; }
		std::string get_author() const { return author; }
		void set_author(std::string a) { author = a; }
		std::string get_isbn() const { return isbn; }
		void set_isbn(std::string i) { isbn = i; }
		bool get_available() const { return available; }
		void set_available(bool io) { available = io; }
	};

	// proper ISBN input is of the form  n-n-n-x  where n is an integer and x is an int or a letter
	//	ISBNs will be stored as  nnnx.
	bool is_isbn(std::string &isbn);

	// overload << operator so that it is easy to print a book's information
	std::ostream& operator<<(std::ostream& os, const Book& b);

	// Books are the same if their ISBN is the same
	bool operator==(const Book& a, const Book& b);

	bool operator!=(const Book& a, const Book& b);

	// ///////////////////////////

	// create class in which to store books and query the library stock

	class Library {
	public:
		std::vector<Book> contents = {};		// to store the books
		int is_book(std::string title);		// if a title is in contents, returns the index; otherwise returns -1
		bool add_book(Book& b);			// true if b's isbn is not already used by another book in contents
	};

	// ///////////////////////////

	// check to see if a book can be checked in or checked out, based on value of status
	void check_io(Library lib_name, std::string title, std::string io);
}

#endif