// Currency Converter program which reads countries' values relative to the USD from a file, 
//  and then opens a window for user input.  

#include "Currency.h"
#include <iostream>
#include <vector>
#include <string>

// headers required for graphics use in Programming Practices and Principles Using C++
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/fltk.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Simple_window.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Graph.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/GUI.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Point.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Window.h"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Graph.cpp"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/GUI.cpp"
#include "C:/Users/zackb_000/Documents/Visual Studio 2017/Projects/ProgrammingPrincPracC/Window.cpp"

struct Converter_window : Window {
	Converter_window(Point xy, int w, int h, const string& title,
		std::vector<Conversion> ratios);
private:
	// data:
	std::vector<Conversion> ratios;

	// widets:
	Button quit_button;
	Button convert_button;	// do the conversion
	In_box i_denom;			// initial denomination
	In_box f_denom;			// final denomination
	In_box money_input;		// initial value
	Out_box money_output;	// converted value
	Out_box supported;		// hack to show supported currencies list

	// actions invoked by callbacks: 
	void quit() { hide(); } // FLTK solution
	void convert_pressed();

	// callback functions:
	static void cb_quit(Address, Address pw)
	{
		reference_to<Converter_window>(pw).quit();
	}
	static void cb_convert(Address, Address pw)
	{
		reference_to<Converter_window>(pw).convert_pressed();
	}
};

Converter_window::Converter_window(Point xy, int w, int h, const string& title,
	std::vector<Conversion> ratios)
	:Window{ xy,w,h,title },	// initialize the window where the program lives
	ratios{ ratios },
	quit_button{ Point{x_max() - 70,0},70,20,"Quit",cb_quit },
	convert_button{ Point{x_max() - 310,52}, 120, 20, "Convert Currency", cb_convert },
	i_denom{ Point{x_max() - 400,40}, 70, 20, "Initial Denom.:" },
	f_denom{ Point{x_max() - 80,40}, 70, 20, "Final Denom.:" },
	money_input{ Point{x_max() - 400,65}, 70, 20,"Initial Value:" },
	money_output{ Point{x_max() - 80,65}, 70, 20, "Final Value:" },
	supported{ Point{x_max() - 500, 95}, 400, 20, "" }
{
	attach(supported);
	attach(quit_button);
	attach(convert_button);
	attach(i_denom);
	attach(f_denom);
	attach(money_input);
	attach(money_output);
	attach(supported);
	// put the country names from the vector ratios in supported's field
	std::string countries = get_countries(ratios);
	supported.put("Supported: " + countries);
}

void Converter_window::convert_pressed()
{
	// can't get a double from an In_box, so get a string and convert
	std::string value_in_str = money_input.get_string();
	double value_in_d = str_to_double(value_in_str);
	std::string initial_cur = i_denom.get_string();
	std::string final_cur = f_denom.get_string();
	double value_out_d = convert_money(value_in_d, initial_cur, final_cur, ratios);
	// can't put a double into an Out_box, so convert the double to a string
	std::string value_out_str = double_to_str(value_out_d);
	money_output.put(value_out_str);
}

int main()
try {
	std::string conversion_file = "currencies.txt";
	std::vector<Conversion> ratios = read_ratios("currencies.txt");
	Converter_window win{ {100,100},600,200,"Currencty Converter",ratios };
	return gui_main();
}
catch (my_error& caught) {
	std::cout << caught.what() << std::endl;
}