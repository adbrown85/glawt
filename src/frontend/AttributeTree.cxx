/*
 * AttributeTree.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include <gtkmm/main.h>
#include "AttributeTree.hpp"


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	
	// Test
	AttributeTree tree;
	tree.append("1", "apple");
	tree.push();
		tree.append("1-1", "mango");
		tree.append("1-2", "guava");
		tree.pop();
	tree.append("2", "pear");
	tree.push();
		tree.append("2-1", "orange");
		tree.push();
			tree.append("2-1-1", "peach");
			tree.append("2-1-2", "banana");
			tree.append("2-1-3", "blueberry");
			tree.pop();
		tree.pop();
	tree.append("3", "lemon");
	tree.print();
	
	try {
		tree.pop();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

