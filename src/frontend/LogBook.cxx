/*
 * LogBook.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "LogBook.hpp"


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	LogBook lb;
	
	// Set up window
	window.add(lb);
	window.set_title("LogBook");
	window.show_all_children();
	
	// Run
	Gtk::Main::run(window);
	return 0;
}

