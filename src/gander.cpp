/*
 * Client.cpp
 *     Client for visualizing volumes.
 * 
 * Author
 *     Andrew Brown
 */
#include "Client.hpp"



Client::Client() {
	
	// Initialize
	scene = NULL;
}



Client::~Client() {
	
	// Deallocate
	if (scene != NULL)
		delete scene;
}



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
	if (argc != 3) {
		cerr << "Usage: " << argv[0]
		                  << " -f <filename>" << endl;
		cerr << "  f XML scene file" << endl;
		exit(1);
	}
	for (int i=1; i<argc; i++)
		if (strcmp(argv[i], "-f") == 0)
			sceneFilename = argv[++i];
}



/**
 * Sets the name of the Client from a filename
 * 
 * @param filename
 *     Path to the Client as specified on the command line.
 */
void Client::setName(string filename) {
	
	int index, length;
	
	// Remove directory part
	index = filename.rfind('/');
	if (index < filename.length())
		name = filename.erase(0, index+1);
	
	// Fix case
	length = name.length();
	for (int i=0; i<length; ++i)
		name[i] = tolower(name[i]);
	name[0] = toupper(name[0]);
}



/**
 * Starts the Client.
 */
void Client::start() {
	
	// Open scene
	scene = new Scene(640, 480);
	Interpreter interpreter(scene);
	interpreter.run(Command::OPEN, sceneFilename);
	
	// Install controls
	Keyboard keyboard(&interpreter);
	Menu menu(&interpreter);
	Mouse mouse(&interpreter);
	Display::install(&keyboard);
	Display::install(&menu);
	Display::install(&mouse);
	
	// Start display
	Display::start("Gander", scene);
}



/**
 * Simple test program.
 */
int main(int argc, char **argv) {
	
	Client client;
	
	// Handle arguments
	client.parse(argc, argv);
	client.setName(argv[0]);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << client.getName() << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	client.start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << client.getName() << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
