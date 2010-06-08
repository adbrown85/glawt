/*
 * Menu.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Menu.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>


int main(int argc,
         char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	Menu *menu;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Menu" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	menu = new Menu(NULL);
	window.set_title("Menu Test");
	window.add(*(menu->getMenuBar()));
	window.show_all();
	Gtk::Main::run(window);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Menu" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

