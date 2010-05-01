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
 * @param argc Number of arguments.
 * @param argv Array of arguments as C-strings.
 */
Client::Client(int argc,
               char *argv[]) {
	
	this->argc = argc;
	this->argv = argv;
	this->display = NULL;
	this->interpreter = NULL;
	this->scene = NULL;
}


Client::~Client() {
	
	if (display != NULL)
		delete display;
	if (interpreter != NULL)
		delete interpreter;
	if (scene != NULL)
		delete scene;
}


void Client::banner() {
	
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


void Client::onCompile() {
	
	// Create window
	Window::init(argc, argv);
	Window::create(title);
	
	// Open scene
	scene = new Scene();
	interpreter = new Interpreter(scene);
	interpreter->run(Command::OPEN, inFilename);
}


/**
 * Starts the display for a scene.
 * 
 * @note Controls are not deleted.
 */
void Client::onDisplay() {
	
	// Create window
	Window::init(argc, argv);
	Window::create(title);
	
	// Open scene
	scene = new Scene();
	interpreter = new Interpreter(scene);
	interpreter->run(Command::OPEN, inFilename);
	
	// Add display and controls
	display = new Display(interpreter);
	display->add(new Keyboard(interpreter));
	display->add(new Menu(interpreter));
	display->add(new Mouse(interpreter));
	
	// Start
	Window::start();
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
	
	// Initialize
	parse();
	title = string("Gander [") + inFilename + "]";
	
	// Handle option
	if (option == "--preprocess") {
		onPreprocess();
	} else if (option == "--vlb") {
		onVlb();
	} else if (option == "--header") {
		onHeader();
	} else if (option == "--compile") {
		onCompile();
	} else {
		banner();
		onDisplay();
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
	cerr << "  --display        Display a scene (the default)" << endl;
	cerr << "  --compile        Compile but do not display scene" << endl;
	cerr << "  --preprocess     Preprocess GLSL file" << endl;
	cerr << "  --vlb            Make VLB volume file" << endl;
	cerr << "  --header         Print header of VLB file" << endl;
}

