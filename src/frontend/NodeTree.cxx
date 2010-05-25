/*
 * NodeTree.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include <gtkmm/main.h>
#include "NodeTree.hpp"
#include "Scene.hpp"
#include "BasicFactory.hpp"


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::Window window;
	Scene scene;
	NodeTree tree;
	
	// Test
	BasicFactory::install();
	scene.open("NodeTree.xml");
	tree.append(scene.getRoot());
	tree.push();
	tree.append(*(scene.getRoot()->begin()));
	tree.pop();
	tree.print();
	
	try {
		tree.pop();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	window.show_all_children();
	Gtk::Main::run(window);
	return 0;
}

