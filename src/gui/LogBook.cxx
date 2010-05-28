/*
 * LogBook.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "LogBook.hpp"


int main(int argc, char *argv[]) {
	
	using System::log;
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	LogBook logBook;
	
	// Set up window
	window.add(logBook);
	window.set_title("LogBook");
	window.show_all_children();
	
	// Put some message in the log
	log << "This is a message!" << endl;
	log << "This is another message!" << endl;
	log << "Yet another message!" << endl;
	
	// Run
	Gtk::Main::run(window);
	return 0;
}

