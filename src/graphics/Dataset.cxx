/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include "Dataset.hpp"
#include "DatasetViewer.hpp"
#include "CanvasGTK.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>


int main(int argc, char *argv[]) {
	
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
		
		// Initialize
		Gtk::Main kit(argc, argv);
		Gtk::GL::init(argc, argv);
		
		// Set up the dataset
		Dataset dataset(filename);
		dataset.load();
		dataset.print();
		
		// Create the viewer
		CanvasGTK canvas(dataset.getWidth(), dataset.getHeight());
		DatasetViewer viewer;
		viewer.setCanvas(&canvas);
		viewer.setDataset(&dataset);
		viewer.load();
		
		// Pack
		Gtk::Window window;
		window.set_title(dataset.getFilename());
		window.add(canvas);
		window.show_all_children();
		
		// Run
		Gtk::Main::run(window);
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

