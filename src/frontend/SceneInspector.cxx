/*
 * SceneInspector.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "SceneInspector.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	SceneInspector inspector;
	Scene scene;
	
	// Create the examiner
	BasicFactory::install();
	scene.open("SceneInspector.xml");
	inspector.setScene(&scene);
	
	// Add it to the window and start
	window.add(inspector);
	window.set_title("Scene Inspector");
	window.show_all_children();
	inspector.update();
	Gtk::Main::run(window);
	return 0;
}

