/*
 * DatasetViewer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetViewer.hpp"
#include <cstring>
#include "Toolkit.hpp"
#include "CanvasFactory.hpp"
#include "WindowFactory.hpp"


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
	
	Window *window;
	Canvas *canvas;
	
	try {
		
		// Set up the dataset
		Dataset dataset(filename);
		dataset.load();
		dataset.print();
		
		// Initialize
		Toolkit kit(argc, argv);
		
		// Window and canvas
		window = WindowFactory::create();
		canvas = CanvasFactory::create(dataset.getWidth(), dataset.getHeight());
		
		// Create the viewer
		DatasetViewer viewer;
		viewer.setCanvas(canvas);
		viewer.setDataset(&dataset);
		viewer.load();
		
		// Pack window
		window->setTitle(dataset.getFilename());
		window->add(canvas);
		window->show();
		
		// Run
		window->run();
		delete window;
		delete canvas;
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

