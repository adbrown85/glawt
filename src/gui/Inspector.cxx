/*
 * Inspector.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "Inspector.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
#ifdef HAVE_GTK
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	Inspector inspector;
	Scene scene;
	
	// Create the examiner
	BasicFactory::install();
	scene.open("Inspector.xml");
	inspector.setScene(&scene);
	
	// Add it to the window and start
	window.add(inspector);
	window.set_title("Inspector");
	window.show_all_children();
	inspector.update();
	Gtk::Main::run(window);
#endif
	return 0;
}

