/*
 * Application.cpp
 *     Application for visualizing volumes.
 * 
 * Author
 *     Andrew Brown
 */
#include "Application.hpp"



/**
 * Creates a new Application object.
 */
Application::Application() {
	
	// Initialize
	scene = NULL;
}



/**
 * Cleans up memory allocated by the Application.
 */
Application::~Application() {
	
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
void Application::parse(int argc,
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
 * Starts the Application.
 */
void Application::start() {
	
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
	
	Application application;
	
	// Handle arguments
	application.parse(argc, argv);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Application" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	application.start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Application" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
