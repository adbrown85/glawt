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


bool onScrollEvent(GdkEventScroll* event) {
	
	cout << "onScrollEvent()" << endl;
	return false;
}


void createAndShowGUI() {
	
	Gtk::Window window;
	Gtk::EventBox box;
	
	// Create the canvas
	canvas = new Canvas();
	canvas->setDisplayCallback(&display);
	canvas->setMouseCallback(&mouse);
	canvas->setKeyboardCallback(&keyboard);
	canvas->setDragCallback(&drag);
	
	// Create events
	box.add_events(Gdk::SCROLL_MASK);
	box.signal_scroll_event().connect(sigc::ptr_fun(&onScrollEvent));
	
	// Add to window
	window.set_title("Canvas");
	box.add(*canvas);
	window.add(box);
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

