/*
 * Client.cpp
 *     Client for visualizing volumes.
 * 
 * Author
 *     Andrew Brown
 */
#include "Client.hpp"



/**
 * Parses the command line arguments.
 * 
 * @param argc
 *     Number of arguments.
 * @param argv
 *     Array of arguments as C-strings.
 */
void Client::parse(int argc,
                   char *argv[]) {
	
	// Handle arguments
	if (argc != 2) {
		cerr << "Usage: " << argv[0]
		                  << " <filename>" << endl;
		cerr << "  filename: XML scene file" << endl;
		exit(1);
	}
	filename = argv[1];
}



/**
 * Starts the Client.
 */
void Client::start() {
	
	Interpreter interpreter(&scene);
	Keyboard keyboard(&interpreter);
	Menu menu(&interpreter);
	Mouse mouse(&interpreter);
	
	// Install controls
	Display::install(&keyboard);
	Display::install(&menu);
	Display::install(&mouse);
	
	// Start display
	scene.setFilename(filename);
	title = "Gander [";
	title += filename + "]";
	Display::start(title, &scene, &interpreter);
}



/**
 * Simple test program.
 */
int main(int argc, char **argv) {
	
	Client client;
	
	// Handle arguments
	client.parse(argc, argv);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	client.start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

