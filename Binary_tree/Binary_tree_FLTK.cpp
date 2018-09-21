// Binary_tree is a class that, given the number of rows and desired spacing, produces a binary tree.

//  NOTE: due to the complex nature of the required headers and the FLTK compiler/linker settings,
//	 attempts to split this code up into a separate header and cpp file for the classes have failed.
//	 I have elected to keep this somewhat cluttered set up in interest of time.

// recommended headers for the graphics chapters in "Programming Practices and Principles in C++"
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

// start is the location of the root node, rows is the depth of the tree,
//  h_space is the spacing between nodes in the final row, v_space is spacing between rows
class Binary_tree : public Shape {
public:
	Binary_tree(Point start, int rows, int h_space, int v_space, int radius = 5);
protected:
	Point start;				// location of first node
	int rows;					// layers of the tree
	int h_space;				// distance between nodes within the last row
	int v_space;				// distance between rows of nodes
	int radius;					// for the node circles
	void generate_centers();	// store the center of the nodes in centers
	void draw_lines() const;	// override Shape's virtual function	
	virtual void draw_nodes() const;
	void draw_connections() const;
	vector<vector<Point>> centers;		// store the center of the nodes
};
// make sure the binary tree has at least one row before drawing
Binary_tree::Binary_tree(Point start, int rows, int h_space, int v_space, int radius)
	: start{ start }, rows{ rows }, h_space{ h_space }, v_space{ v_space }, radius{ radius }
{
	if (rows > 0) {
		generate_centers();
		draw_lines();
	}
	else
		std::cout << "Empty binary tree." << std::endl;
}
// loads a vector of vectors - each interior vector represents a row, 
//   and contains the centers of the nodes for that row
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
// replaces virtual function from Shape class
void Binary_tree::draw_lines() const {
	// first, draw the circles
	draw_nodes();
	// then connect the nodes
	draw_connections();
}
// draws circles in the locations specified by centers
void Binary_tree::draw_nodes() const {
	for (int i = 0; i < centers.size(); ++i) {
		for (int j = 0; j < centers[i].size(); ++j) {
			Graph_lib::Circle{ centers[i][j], radius }.draw_lines();
		}
	}
}
// draws arcs connecing nodes in the form of partial ellipses
void Binary_tree::draw_connections() const {
	int row_space;
	for (int i = 0; i < rows - 1; ++i) {
		row_space = h_space * std::pow(2, rows - i - 1);
		for (int j = 0; j < centers[i].size(); ++j) {
			// the first two arguments are the top left corner of the box containing the ellipse 
			fl_arc(centers[i][j].x - row_space / 2, centers[i][j].y, row_space, 2 * v_space, 0, 180);
		}
	}
}

// uses rectangles for nodes instead of circles
class Nodeselektor : public Binary_tree {
public:
	Nodeselektor(Point start, int rows, int h_space, int v_space, int ww = 10, int hh = 10);
	void draw_nodes() const;
	int width;
	int height;
};
Nodeselektor::Nodeselektor(Point start, int rows, int h_space, int v_space, int ww, int hh)
	: Binary_tree(start, rows, h_space, v_space), width{ ww }, height{ hh }
{
	draw_lines(); // a Binary_tree function that calls Nodeselektor::draw_nodes() (it replaces Binary_tree's
				  //  virtual function of the same name), and Binary_tree::draw_connections().
}
// nodes are boxes instead of circles (as in Binary_tree)
void Nodeselektor::draw_nodes() const {
	for (int i = 0; i < centers.size(); ++i) {
		for (int j = 0; j < centers[i].size(); ++j) {
			// the point that determines a rectangle is the top left corner, not the center
			Point tl(centers[i][j].x - width / 2, centers[i][j].y - height / 2);
			Graph_lib::Rectangle{ tl, width, height }.draw_lines();
		}
	}
}

int main() {
	Simple_window win{ {0,0},1600,800,"Binary Tree" };
	Binary_tree bin_tree{ {800,10},5,40,70, 20 };
	bin_tree.set_color(Color::black);
	win.attach(bin_tree);
	win.wait_for_button();
	Nodeselektor bin_tree2{ {800,25}, 3, 40, 80 };
	win.attach(bin_tree2);
	bin_tree2.set_color(Color::red);
	win.wait_for_button();
}
