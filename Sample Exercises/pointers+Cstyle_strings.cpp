#include<iostream>

using namespace std;

// print a C-style string
void print(const char* cst) {
	if (!cst)
		cout << "Null pointer.";
	while (*cst != '\0') {
		cout << *cst;
		++cst;
	}
}

// calculate the length of a C-style string
int myStrLen(const char* cst) {
	if (!cst)
		return -1;
	int i = 0;
	while (*cst != '\0') {
		++i;
		++cst;
	}
	return i;
}

// copy a C-style string into memory allocated on the free store
//	(do not use subscripting or standard library functions)
char* myStrdup(const char* cc) {
	size_t l = myStrLen(cc);
	char* fc = new char[l + 1];	// allocated sufficient space
	while (*cc) {	// iterate through cc and copy to fc
		*fc = *cc;
		++fc;
		++cc;
	}
	*fc = '\0';		// terminate the C-style string
	fc -= l;		// point back to the start of fc
	return fc;
}

// find the first occurence of the C-style string x in s without
//	using library functions or subscripting
char* findx(const char* s, const char* x) {
	char* s2 = const_cast<char*>(s);	// make non-constant to enable 
	char* x2 = const_cast<char*>(x);	//  pointer arithmetic
	size_t slen = myStrLen(s);
	size_t xlen = myStrLen(x);
	for (size_t i = 0; i < slen - xlen; ++i) {
		if (*s2 == *x2) {
			size_t j = 0;
			while (*x2) {
				(*s2 == *x2) ? ++j : j = 0;
				++x2;	// increment at the end of the loop
				++s2;	//  otherwise, the last loop will go over the end 
			}			//  of the c-style string
			if (j == xlen)	// only true if *s2 = *x2 for all chars in x2
				return s2 - xlen;
			else {		// go back to where the comparison started
				s2 -= xlen;
				x2 -= xlen;
			}
		}
		++s2;	// only increment s2 since we want to compare to the
	}			//  beginning of x2
	return nullptr;		// no match found
}

// recursive function that compares C-style strings. 
//  return (-1,0,1) means s1 was lexicographically 
//  (before,equal,after) s2
int strcmp(char* s1, char* s2) {
	if (!*s1 && !*s2)	// at the end of both strings,
		return 0;		//  they are equal
	if (!*s1)			// s1 and s2 match until the end of s1,
		return -1;		//  s1 comes before s2
	if (!*s2)
		return 1;
	// check the lexicographical arrangement of the current letter
	if (int(*s1) < int(*s2))
		return -1;
	if (int(*s2) < int(*s1))
		return 1;
	// letters were the same, check the next letter
	strcmp(++s1, ++s2);
}

// describes lexicographical placement of s1 and s2 based
//	on the value of n
void print_lexi(char* s1, char* s2, int n) {
	switch (n) {
	case -1:
		print(s1);
		cout << " comes before ";
		print(s2);
		cout << endl;
		break;
	case 0:
		print(s1);
		cout << " is the same as ";
		print(s2);
		cout << endl;
		break;
	case 1:
		print(s1);
		cout << " comes after ";
		print(s2);
		cout << endl;
		break;
	}
}

int main() {
	// test myStrdup(const char*)
	char cstr1[] = { 'a','e','i','o','u','\0', };
	char* cstr2 = myStrdup(cstr1);
	print(cstr2);
	cout << endl;
	delete[] cstr2;
	// test findx(const char*, const char*)
	char cstr3[] = { 'e', 'i', '\0' };
	char* xloc = findx(cstr1, cstr3);
	if (xloc)
		cout << "Match found starting at " << *xloc << "." << endl;
	else
		cout << "No match found." << endl;
	// test strcmp(char*, char*)
	int loc = strcmp(cstr1, cstr3);
	print_lexi(cstr1, cstr3, loc);
	// keep window open
	cin.get();
}