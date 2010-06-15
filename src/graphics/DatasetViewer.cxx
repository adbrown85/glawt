/*
 * DatasetViewer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include "Dataset.hpp"
#include "DatasetViewer.hpp"
#ifdef HAVE_GTK
#include "CanvasGTK.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#endif


int main(int argc, char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bunny128.vlb";
	} else if (argc == 2) {
		filename = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " [<filename>]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetViewer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Set up the dataset
		Dataset dataset(filename);
		dataset.load();
		dataset.print();
		
		// Initialize window
#ifdef HAVE_GTK
		Gtk::Main kit(argc, argv);
		Gtk::GL::init(argc, argv);
		Gtk::Window window;
		CanvasGTK canvas(dataset.getWidth(), dataset.getHeight());
#endif
		
		// Create the viewer
		DatasetViewer viewer;
		viewer.setCanvas(&canvas);
		viewer.setDataset(&dataset);
		viewer.load();
		
		// Pack and run window
#ifdef HAVE_GTK
		window.set_title(dataset.getFilename());
		window.add(canvas);
		window.show_all_children();
		Gtk::Main::run(window);
#endif
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

