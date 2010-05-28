/*
 * TextTree.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include <gtkmm/main.h>
#include "TextTree.hpp"


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	
	// Test
	TextTree tree;
	tree.add("1");
	tree.push();
		tree.add("1-1");
		tree.add("1-2");
		tree.pop();
	tree.add("2");
	tree.push();
		tree.add("2-1");
		tree.push();
			tree.add("2-1-1");
			tree.add("2-1-2");
			tree.add("2-1-3");
			tree.pop();
		tree.pop();
	tree.add("3");
	tree.print();
	
	try {
		tree.pop();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

