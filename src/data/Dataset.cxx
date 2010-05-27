/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include "Dataset.hpp"
#include "DatasetViewer.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>


int main(int argc, char *argv[]) {
	
	Dataset *dataset;
	DatasetViewer *viewer;
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bear.vlb";
	} else if (argc == 2) {
		filename = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " [<filename>]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Set up the dataset
		dataset = new Dataset(filename);
		dataset->load();
		dataset->print();
		
		// Set up window
		Gtk::Main kit(argc, argv);
		Canvas::init(argc, argv);
		Gtk::Window window;
		
		// Create the viewer
		viewer = new DatasetViewer();
		viewer->setDataset(dataset);
		
		// Pack
		window.set_title(dataset->getFilename());
		window.add(*viewer);
		window.show_all_children();
		
		// Run
		Gtk::Main::run(window);
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

