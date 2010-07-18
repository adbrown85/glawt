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
	this->canvas = NULL;
	this->window = NULL;
}


Gander::~Gander() {
	
	if (display != NULL)
		delete display;
	if (delegate != NULL)
		delete delegate;
	if (scene != NULL)
		delete scene;
	if (canvas != NULL)
		delete canvas;
	if (window != NULL)
		delete window;
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
	
	// Create window and canvas
	window = WindowFactory::create();
	canvas = CanvasFactory::create();
	
	// Create widgets
	scene = new Scene();
	delegate = new Delegate(scene, canvas);
	controls.push_back(new Mouse(delegate));
	controls.push_back(new Keyboard(delegate));
	
	// Pack
	window->setTitle(title);
	onDisplayPack();
	window->show();
	
	// Prime the canvas
	canvas->primeStart();
	prime();
	canvas->primeFinish();
	
	// Finalize
	onDisplayFinalize();
	
	// Run
	window->run();
}


void Gander::onDisplayPack() {
	
	onDisplayPackGTK();
	onDisplayPackGLUT();
}


void Gander::onDisplayPackGTK() {
#ifdef HAVE_GTK
	
	// Create additional widgets
	Gtk::HBox hBox;
	Gtk::VBox mainBox, vBox;
	Inspector inspector;
	LogBook logBook;
	//Menu menu(delegate, &window, controls);
	
	// Pack
	vBox.pack_start(*((CanvasGTK*)canvas), Gtk::PACK_SHRINK);
	vBox.pack_start(logBook);
	hBox.pack_start(inspector);
	hBox.pack_start(vBox, Gtk::PACK_SHRINK);
	//mainBox.pack_start(*(menu.getMenuBar()), Gtk::PACK_SHRINK);
	mainBox.pack_start(hBox);
	window->add(mainBox);
	//window.set_icon_from_file(Resources::getSquareIconFilename());
	
	// Finalize
	inspector.setScene(scene);
	inspector.setCanvas(canvas);
	//inspector.update();
#endif
}


void Gander::onDisplayPackGLUT() {
#ifdef HAVE_GLUT
	
	window->add(canvas);
#endif
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
	
	Preprocessor pp(inFilename);
	
	pp.start();
	pp.printLines();
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
	cerr << "  --slices         View the slices of dataset" << endl;
	cerr << "  --header         Print header of volume file" << endl;
	cerr << "  --range          Find actual high and low of dataset" << endl;
	cerr << "  --histogram      Show distribution in dataset" << endl;
	cerr << "  --convert [i]    Convert volume taking every i'th voxel" << endl;
}


int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	Gander gander(argc, argv);
	
	try {
		gander.start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	return 0;
}

