/*
 * LogBook.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "LogBook.hpp"


int main(int argc, char *argv[]) {
	
#ifdef HAVE_GTK
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	LogBook logBook;
	
	// Set up window
	window.add(logBook);
	window.set_title("LogBook");
	window.show_all_children();
	
	// Put some message in the log
	glog << "This is a message!" << endl;
	glog << "This is another message!" << endl;
	glog << "Yet another message!" << endl;
	
	// Run
	Gtk::Main::run(window);
#endif
	return 0;
}

