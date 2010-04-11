/*
 * Client.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Client.hpp"


/**
 * Creates a %Client.
 * 
 * @param argc
 *     Number of arguments.
 * @param argv
 *     Array of arguments as C-strings.
 */
Client::Client(int argc,
               char *argv[]) {
	
	this->argc = argc;
	this->argv = argv;
}


void Client::banner() {
	
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


/**
 * Starts the display for a scene.
 */
void Client::display() {
	
	Interpreter interpreter(&scene);
	Keyboard keyboard(&interpreter);
	Menu menu(&interpreter);
	Mouse mouse(&interpreter);
	
	// Install controls
	Display::install(&keyboard);
	Display::install(&menu);
	Display::install(&mouse);
	
	// Start display
	scene.setFilename(inFilename);
	title = "Gander [";
	title += inFilename + "]";
	Display::start(argc, argv, title, &scene, &interpreter);
}


void Client::onHeader() {
	
	DatasetHeader header(inFilename);
	
	header.print();
}


void Client::onPreprocess() {
	
	Preprocessor pp(inFilename);
	
	pp.start();
	pp.printLines();
}


void Client::onVlb() {
	
	VlbMaker vlbMaker(inFilename, outFilename);
	
	vlbMaker.start();
}


/**
 * Parses the command line arguments.
 */
void Client::parse() {
	
	// Handle arguments
	if (argc == 2) {
		inFilename = argv[1];
	} else if (argc == 3) {
		option = argv[1];
		inFilename = argv[2];
	} else if (argc == 4) {
		option = argv[1];
		inFilename = argv[2];
		outFilename = argv[3];
	} else {
		usage();
		exit(1);
	}
}


/**
 * Starts the actions.
 */
void Client::start() {
	
	parse();
	if (option == "--preprocess") {
		onPreprocess();
	} else if (option == "--vlb") {
		onVlb();
	} else if (option == "--header") {
		onHeader();
	} else {
		banner();
		display();
		banner();
	}
}


/**
 * Prints a usage message.
 */
void Client::usage() {
	
	cerr << "Usage: " << argv[0] << " [OPTION] INPUT [OUTPUT]" << endl;
	cerr << endl;
	cerr << "Options: " << endl;
	cerr << "  --preprocess     Preprocess GLSL file" << endl;
	cerr << "  --vlb            Make VLB volume file" << endl;
	cerr << "  --header         Print header of VLB file" << endl;
}

