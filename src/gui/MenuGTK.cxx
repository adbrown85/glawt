/*
 * MenuGTK.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MenuGTK.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>


int main(int argc,
         char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	MenuGTK *menu;
	list<Control*> controls;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MenuGTK" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	menu = new MenuGTK(NULL, &window, controls);
	window.set_title("MenuGTK Test");
	window.add(*(menu->getMenuBar()));
	window.show_all();
	Gtk::Main::run(window);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MenuGTK" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

