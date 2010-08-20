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
	this->delegate = NULL;
	this->scene = NULL;
}


Gander::~Gander() {
	
	if (display != NULL)
		delete display;
	if (delegate != NULL)
		delete delegate;
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
	
	// Initialize
	Toolkit kit(argc, argv);
	
	// Create window and canvas
	window = WindowFactory::create();
	canvas = CanvasFactory::create();
	
	// Create widgets
	scene = new Scene();
	delegate = new Delegate(scene, canvas);
	
	// Pack
	window->add(canvas);
	window->show();
	
	// Do setup
	canvas->primeStart();
	prime();
	canvas->primeFinish();
	
	// Cleanup
	delete window;
	delete canvas;
}


void Gander::onConvert() {
	
	DatasetWriter writer;
	
	writer.setInput(inFilename);
	writer.setOutput(outFilename);
	if (!parameter.empty())
		writer.setJump(atoi(parameter.c_str()));
	writer.write();
}


/** Starts the display for a scene.
 * 
 * @note Controls are not deleted.
 */
void Gander::onDisplay() {
	
	// Initialize
	Toolkit kit(argc, argv);
	
	// Create window and canvas
	window = WindowFactory::create();
	canvas = CanvasFactory::create();
	
	// Create widgets
	scene = new Scene();
	delegate = new Delegate(scene, canvas);
	controls.push_back(new Mouse(delegate));
	controls.push_back(new Keyboard(delegate));
#ifdef HAVE_GLUT
	controls.push_back(new MenuGLUT(delegate));
#endif
	
	// Create additional widgets
#ifdef HAVE_GTK
	Gtk::HBox hBox;
	Gtk::VBox mainBox, vBox;
	LogBook logBook;
	Inspector inspector;
	MenuGTK menu(delegate, (Gtk::Window*)window->getNativeWindow(), controls);
#endif
	
	// Pack
#ifdef HAVE_GTK
	vBox.pack_start(*((CanvasGTK*)canvas), Gtk::PACK_SHRINK);
	vBox.pack_start(logBook);
	hBox.pack_start(inspector);
	hBox.pack_start(vBox, Gtk::PACK_SHRINK);
	mainBox.pack_start(*(menu.getMenuBar()), Gtk::PACK_SHRINK);
	mainBox.pack_start(hBox);
	((WindowGTK*)window)->add(mainBox);
#else
	window->add(canvas);
#endif
	
	// Show
	window->setIcon(Resources::getSquareIconFilename());
	window->setTitle(title);
	window->show();
	
	// Prime the canvas
	canvas->primeStart();
	prime();
	canvas->primeFinish();
	
	// Finalize
#ifdef HAVE_GTK
	inspector.setScene(scene);
	inspector.setCanvas(canvas);
	inspector.update();
#endif
	
	// Run
	window->run();
	
	// Cleanup
	delete window;
	delete canvas;
}


void Gander::onHeader() {
	
	DatasetHeader header(inFilename);
	
	header.print();
}


void Gander::onHistogram() {
	
	Dataset dataset(inFilename);
	DatasetAnalyzer analyzer;
	clock_t ticks;
	
	dataset.load(true);
	analyzer.setDataset(&dataset);
	cout << "Computing histogram..." << endl;
	ticks = clock();
	analyzer.printHistogram();
	cout << (double)(clock() - ticks) / CLOCKS_PER_SEC << "s" << endl;
}


void Gander::onPreprocess() {
	
	CodeLoader pp;
	
/*
	pp.parse(inFilename);
	pp.printLines();
*/
}


void Gander::onRange() {
	
	Dataset dataset(inFilename);
	DatasetAnalyzer analyzer;
	clock_t ticks;
	
	dataset.load(true);
	analyzer.setDataset(&dataset);
	cout << "Computing actual range..." << endl;
	ticks = clock();
	analyzer.printRange();
	cout << (double)(clock() - ticks) / CLOCKS_PER_SEC << "s" << endl;
}


void Gander::onSlices() {
	
	// Initialize
	Toolkit kit(argc, argv);
	
	// Load the dataset
	Dataset dataset(inFilename);
	dataset.load();
	dataset.print();
	
	// Create window and canvas
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
	
	// Clean up
	delete window;
	delete canvas;
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
	} else if (argc == 5) {
		option = argv[1];
		parameter = argv[2];
		inFilename = argv[3];
		outFilename = argv[4];
	} else {
		usage();
		exit(1);
	}
}


/** Opens the scene and creates the display. */
void Gander::prime() {
	
	list<Control*>::iterator it;
	
	// Open scene
	delegate->run(Command::OPEN, inFilename);
	
	// Add display and controls
	display = new Display(delegate);
	for (it=controls.begin(); it!=controls.end(); ++it) {
		(*it)->load();
		display->add(*it);
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
	} else if (option == "--slices") {
		onSlices();
	} else if (option == "--header") {
		onHeader();
	} else if (option == "--compile") {
		onCompile();
	} else if (option == "--convert") {
		onConvert();
	} else if (option == "--range") {
		onRange();
	} else if (option == "--histogram") {
		onHistogram();
	} else {
		onDisplay();
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
	cerr << "  --slices         View the slices of dataset" << endl;
	cerr << "  --header         Print header of volume file" << endl;
	cerr << "  --range          Find actual high and low of dataset" << endl;
	cerr << "  --histogram      Show distribution in dataset" << endl;
	cerr << "  --convert [i]    Convert volume taking every i'th voxel" << endl;
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

