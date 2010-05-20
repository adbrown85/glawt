/*
 * gander.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gander.hxx"


/** Creates an instance of the application. */
Gander::Gander(int argc, char *argv[]) {
	
	this->argc = argc;
	this->argv = argv;
	this->display = NULL;
	this->interpreter = NULL;
	this->scene = NULL;
}


Gander::~Gander() {
	
	if (display != NULL)
		delete display;
	if (interpreter != NULL)
		delete interpreter;
	if (scene != NULL)
		delete scene;
}


void Gander::banner() {
	
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


void Gander::onCompile() {
	
	// Create window
	Window::init(argc, argv);
	Window::create(title);
	
	// Open scene
	scene = new Scene();
	interpreter = new Interpreter(scene);
	interpreter->run(Command::OPEN, inFilename);
}


/** Starts the display for a scene.
 * 
 * @note Controls are not deleted.
 */
void Gander::onDisplay() {
	
	// Create window
	Window::init(argc, argv);
	Window::create(title);
	
	// Open scene
	scene = new Scene();
	interpreter = new Interpreter(scene);
	interpreter->run(Command::OPEN, inFilename);
	interpreter->run(Command::LIST);
	
	// Add display and controls
	display = new Display(interpreter);
	display->add(new Keyboard(interpreter));
	display->add(new Menu(interpreter));
	display->add(new Mouse(interpreter));
	
	// Start
	Window::start();
}


void Gander::onHeader() {
	
	DatasetHeader header(inFilename);
	
	header.print();
}


void Gander::onPreprocess() {
	
	Preprocessor pp(inFilename);
	
	pp.start();
	pp.printLines();
}


void Gander::onVlb() {
	
	VlbMaker vlbMaker(inFilename, outFilename);
	
	vlbMaker.start();
}


/** Parses the command line arguments. */
void Gander::parse() {
	
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


/** Starts the actions. */
void Gander::start() {
	
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


/** Prints a usage message. */
void Gander::usage() {
	
	cerr << "Usage: " << argv[0] << " [OPTION] INPUT [OUTPUT]" << endl;
	cerr << endl;
	cerr << "Options: " << endl;
	cerr << "  --display        Display a scene (the default)" << endl;
	cerr << "  --compile        Compile but do not display scene" << endl;
	cerr << "  --preprocess     Preprocess GLSL file" << endl;
	cerr << "  --vlb            Make VLB volume file" << endl;
	cerr << "  --header         Print header of VLB file" << endl;
}


int main(int argc, char *argv[]) {
	
	Gander gander(argc, argv);
	
	try {
		gander.start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	return 0;
}

