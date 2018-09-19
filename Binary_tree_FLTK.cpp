// Binary_tree is a class that, given the number of rows and desired spacing, produces a binary tree.

// recommended headers for the graphics chapters in "Programming Practices and Principles in C++"
//  the graphics package FLTK is required for compilation, \
//  the other headers can be found at http://stroustrup.com/Programming/

#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/fltk.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Simple_window.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Graph.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/GUI.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Point.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Window.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Graph.cpp"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/GUI.cpp"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Window.cpp"
#include <iostream>
#include <cmath>
#include <vector>

using Graph_lib::Point;
using std::pow;

void print_point(Point p) {
	std::cout << p.x << ", " << p.y << std::endl;
}

// start is the location of the root node, rows is the depth of the tree,
//  h_space is the spacing between nodes in the final row, v_space is spacing between rows
class Binary_tree : public Shape {
public:
	Binary_tree(Point start, int rows, int h_space, int v_space1)
		: start{ start }, rows{ rows }, h_space{ h_space }, v_space{ v_space1 }
	{
		if (rows > 0) {
			generate_centers();
			draw_lines();
		}
		else
			std::cout << "Empty binary tree." << std::endl;
	}

private:
	Point start;				// location of first node
	int rows;					// layers of the tree
	int h_space;				// distance between nodes within the last row
	int v_space;				// distance between rows of nodes
	void generate_centers();	// store the center of the nodes in centers
	void draw_lines() const;	// override Shape's virtual function
	vector<vector<Point>> centers;		// store the center of the nodes
};

void Binary_tree::generate_centers() {
	vector<Point> row;
	row.push_back(start);	// the first row is the starting point
	centers.push_back(row);
	row.clear();
	int row_space;
	for (int i = 1; i < rows; ++i) {
		row_space = h_space * std::pow(2, rows - i);	// spacing between two nodes in a row 
		for (int j = 0; j < centers[i - 1].size(); ++j) {
			row.push_back({ centers[i - 1][j].x - row_space / 2, centers[i - 1][j].y + v_space });	// lower left node
			row.push_back({ centers[i - 1][j].x + row_space / 2, centers[i - 1][j].y + v_space });	// lower right node
		}
		centers.push_back(row);
		row.clear();
	}
}

void Binary_tree::draw_lines() const {
	// first, draw the circle
	for (int i = 0; i < centers.size(); ++i) {
		for (int j = 0; j < centers[i].size(); ++j) {
			Graph_lib::Circle{ centers[i][j],5 }.draw_lines();
		}
	}
	// next, draw the connecting arcs
	int row_space;
	for (int i = 0; i < rows - 1; ++i) {
		row_space = h_space * std::pow(2, rows - i - 1);
		for (int j = 0; j < centers[i].size(); ++j) {
			// the first two arguments are the top left corner of the box containing the ellipse 
			fl_arc(centers[i][j].x - row_space / 2, centers[i][j].y, row_space, 2 * v_space, 0, 180);
		}
	}
}

int main() {
	Simple_window win{ {0,0},1600,800,"Binary Tree" };
	Binary_tree bin_tree{ {800,10},5,40,70 };
	bin_tree.set_color(Color::black);
	win.attach(bin_tree);
	win.wait_for_button();
	Binary_tree bin_tree2{ {800,25}, 1, 40, 80 };
	win.attach(bin_tree2);
	bin_tree2.set_color(Color::red);
	win.wait_for_button();
	Binary_tree bin_tree3{ {800,35}, 0, 40, 80 };
	win.attach(bin_tree3);
	bin_tree3.set_color(Color::blue);
	win.wait_for_button();
}