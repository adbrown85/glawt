/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"
Scene Tester::scene;
Traverser *Tester::traverser;
Canvas *Tester::canvas;


/** OpenGL display callback. */
void Tester::display(void) {
	
	// Clear
	canvas->clear();
	
	// Draw
	canvas->applyView();
	traverser->start();
	//canvas->write(scene.getFilename());
	
	// Finish
	canvas->flush();
}


/** Callback for key presses. */
void Tester::keyboard(int key, int x, int y) {
	
	switch(key) {
	case CANVAS_KEY_UP:
		canvas->rotate(-CANVAS_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case CANVAS_KEY_RIGHT:
		canvas->rotate(+CANVAS_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	case CANVAS_KEY_DOWN:
		canvas->rotate(+CANVAS_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case CANVAS_KEY_LEFT:
		canvas->rotate(-CANVAS_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	case 'r':
	case 'R':
		canvas->reset();
		break;
	case CANVAS_MINUS:
		canvas->translate(Vector(0,0,-1));
		break;
	case CANVAS_PLUS:
	case CANVAS_EQUALS:
		canvas->translate(Vector(0,0,+1));
		break;
	case CANVAS_ESCAPE:
	case 'Q':
	case 'q':
		exit(0);
	}
}


void Tester::init(int argc, char *argv[]) {
	
	Canvas::init(argc, argv);
}


/** Callback for mouse clicks. */
void Tester::mouse(int button, int state, int x, int y) {
	
	cerr << "Clicked at (" << x << "," << y << ")." << endl;
}


/** Creates a window, opens the scene, and prepares it. */
void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << FileUtility::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create the canvas
	canvas = new Canvas();
	canvas->setDisplayCallback(&display);
	canvas->setKeyboardCallback(&keyboard);
	canvas->setMouseCallback(&mouse);
	
	// Open and prepare scene
	try {
		scene.open(filename);
		scene.prepare();
		scene.print();
		traverser = new Traverser(&scene);
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}


/** Starts the window's main loop, catching any exceptions. */
void Tester::start() {
	
	Gtk::Window window;
	
	try {
		window.set_title("Tester");
		window.add(*canvas);
		window.show_all();
		Gtk::Main::run(window);
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

