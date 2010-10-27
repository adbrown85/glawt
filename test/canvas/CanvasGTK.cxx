/*
 * CanvasGTK.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Toolkit.hpp"
#include "GLAWTFactory.hpp"


/* Fake canvas listener. */
class FakeCanvasListener : public CanvasListener {
public:
	FakeCanvasListener() {frames = 0;}
	virtual void onCanvasInitEvent(const CanvasEvent &event);
	virtual void onCanvasDisplayEvent(const CanvasEvent &event);
	virtual void onCanvasButtonEvent(const CanvasEvent &event);
	virtual void onCanvasKeyEvent(const CanvasEvent &event);
	virtual void onCanvasDragEvent(const CanvasEvent &event);
private:
	GLuint frames;
};

void FakeCanvasListener::onCanvasInitEvent(const CanvasEvent &event) {

	cout << "FakeCanvasListener::onCanvasInitEvent" << endl;
}

void FakeCanvasListener::onCanvasDisplayEvent(const CanvasEvent &event) {
	
	cout << "FakeCanvasListener::onCanvasDisplayEvent" << endl;
	
	// Update frames
	++frames;
	if (frames > 30) {
		event.source->setAutomaticallyRefresh(false);
	}
	
	// Draw
	glClearColor(0.0, 1.0, 0.0, 1.0);
	event.source->clear();
	event.source->write("This is some text!");
	event.source->flush();
}

void FakeCanvasListener::onCanvasKeyEvent(const CanvasEvent &event) {
	
	switch (event.state.combo.trigger) {
	case TOOLKIT_ESCAPE:
		exit(0);
		break;
	case TOOLKIT_MOD_ALT:
	case TOOLKIT_MOD_CONTROL:
	case TOOLKIT_MOD_SHIFT:
		cout << "Modifier key!" << endl;
		break;
	case TOOLKIT_KEY_DOWN:
	case TOOLKIT_KEY_LEFT:
	case TOOLKIT_KEY_RIGHT:
	case TOOLKIT_KEY_UP:
		cout << "Arrow key!" << endl;
		break;
	default:
		if (isprint((char)event.state.combo.trigger))
			cout << (char)event.state.combo.trigger << endl;
		else
			cout << "Non-printable character." << endl;
	}
}

void FakeCanvasListener::onCanvasButtonEvent(const CanvasEvent &event) {
	
	switch (event.state.combo.trigger) {
	case TOOLKIT_LEFT_BUTTON:
		cout << "Left button!" << endl;
		break;
	case TOOLKIT_MIDDLE_BUTTON:
		cout << "Middle button!" << endl;
		break;
	case TOOLKIT_RIGHT_BUTTON:
		cout << "Right button!" << endl;
		break;
	case TOOLKIT_WHEEL_UP:
		cout << "Wheel up!" << endl;
		break;
	case TOOLKIT_WHEEL_DOWN:
		cout << "Wheel down!" << endl;
		break;
	}
}

void FakeCanvasListener::onCanvasDragEvent(const CanvasEvent &event) {
	
	cout << event.state.x << " " << event.state.y << endl;
}

void createAndShowGUI() {
	
	Window *window;
	Canvas *canvas;
	FakeCanvasListener *listener;
	
	// Create window and canvas
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	
	// Create the listener
	listener = new FakeCanvasListener();
	canvas->addListener(listener);
	canvas->setAutomaticallyRefresh(true);
	
	// Pack window
	window->setTitle("CanvasGTK");
	window->add(canvas);
	window->show();
	
	// Run
	window->run();
	delete window;
	delete canvas;
}

int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	
	// Create window with canvas
	createAndShowGUI();
	return 0;
}

