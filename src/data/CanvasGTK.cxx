/*
 * CanvasGTK.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CanvasGTK.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>


/* Fake canvas listener. */
class FakeCanvasListener : public CanvasListener {
public:
	virtual void onCanvasEvent(const CanvasEvent &event);
	void onDisplayEvent(const CanvasEvent &event);
	void onButtonEvent(const CanvasEvent &event);
	void onKeyEvent(const CanvasEvent &event);
	void onDragEvent(const CanvasEvent &event);
	void setCanvas(Canvas *canvas) {this->canvas = canvas;}
private:
	Canvas *canvas;
};


void FakeCanvasListener::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::BUTTON :
		onButtonEvent(event);
		break;
	case CanvasEvent::DISPLAY :
		onDisplayEvent(event);
		break;
	case CanvasEvent::DRAG :
		onDragEvent(event);
		break;
	case CanvasEvent::KEY :
		onKeyEvent(event);
		break;
	}
}


void FakeCanvasListener::onButtonEvent(const CanvasEvent &event) {
	
	switch (event.state.combo.trigger) {
	case CANVAS_LEFT_BUTTON:
		cout << "Left button!" << endl;
		break;
	case CANVAS_MIDDLE_BUTTON:
		cout << "Middle button!" << endl;
		break;
	case CANVAS_RIGHT_BUTTON:
		cout << "Right button!" << endl;
		break;
	case CANVAS_WHEEL_UP:
		cout << "Wheel up!" << endl;
		break;
	case CANVAS_WHEEL_DOWN:
		cout << "Wheel down!" << endl;
		break;
	}
}


void FakeCanvasListener::onDisplayEvent(const CanvasEvent &event) {
	
	glClearColor(0.0, 1.0, 0.0, 1.0);
	canvas->clear();
	canvas->flush();
}


void FakeCanvasListener::onDragEvent(const CanvasEvent &event) {
	
	cout << event.state.x << " " << event.state.y << endl;
}


void FakeCanvasListener::onKeyEvent(const CanvasEvent &event) {
	
	switch (event.state.combo.trigger) {
	case CANVAS_MOD_ALT:
	case CANVAS_MOD_CONTROL:
	case CANVAS_MOD_SHIFT:
		cout << "Modifier key!" << endl;
		break;
	case CANVAS_KEY_DOWN:
	case CANVAS_KEY_LEFT:
	case CANVAS_KEY_RIGHT:
	case CANVAS_KEY_UP:
		cout << "Arrow key!" << endl;
		break;
	default:
		if (isprint((char)event.state.combo.trigger))
			cout << (char)event.state.combo.trigger << endl;
		else
			cout << "Non-printable character." << endl;
	}
}


void createAndShowGUI() {
	
	Gtk::Window window;
	CanvasGTK *canvas;
	FakeCanvasListener *listener;
	
	// Create the canvas and listener
	canvas = new CanvasGTK();
	listener = new FakeCanvasListener();
	listener->setCanvas(canvas);
	canvas->addListener(listener, CanvasEvent::BUTTON);
	canvas->addListener(listener, CanvasEvent::DISPLAY);
	canvas->addListener(listener, CanvasEvent::DRAG);
	canvas->addListener(listener, CanvasEvent::KEY);
	
	// Add to window
	window.set_title("Canvas");
	window.add(*canvas);
	window.show_all();
	Gtk::Main::run(window);
}


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::GL::init(argc, argv);
	
	// Create window with canvas
	createAndShowGUI();
	return 0;
}

