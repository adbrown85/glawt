/*
 * Canvas.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Canvas.hpp"
Canvas *canvas;


void display() {
	
	glClearColor(0.0, 1.0, 0.0, 1.0);
	canvas->clear();
	
	canvas->flush();
}


void mouse(int button, int state, int x, int y) {
	
	cout << "mouse(int,int,int,int)" << endl;
}


void keyboard(int key, int x, int y) {
	
	cout << "key(int,int,int)" << endl;
}


void drag(int x, int y) {
	
	cout << "drag(int,int)" << endl;
}


void createAndShowGUI() {
	
	Gtk::Window window;
	
	// Create the canvas
	canvas = new Canvas();
	canvas->setDisplayCallback(&display);
	canvas->setMouseCallback(&mouse);
	canvas->setKeyboardCallback(&keyboard);
	canvas->setDragCallback(&drag);
	
	// Add to window
	window.set_title("Canvas");
	window.add(*canvas);
	window.show_all();
	Gtk::Main::run(window);
}


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Canvas::init(argc, argv);
	
	// Create window with canvas
	createAndShowGUI();
	return 0;
}

