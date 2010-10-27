/*
 * CanvasGLUT.cxx
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
	virtual void onCanvasEvent(const CanvasEvent &event);
	void onDisplayEvent(const CanvasEvent &event);
	void onButtonEvent(const CanvasEvent &event);
	void onKeyEvent(const CanvasEvent &event);
	void onDragEvent(const CanvasEvent &event);
	void setCanvas(Canvas *canvas) {this->canvas = canvas;}
private:
	Canvas *canvas;
	GLuint frames;
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

void FakeCanvasListener::onDisplayEvent(const CanvasEvent &event) {
	
	cout << "FakeCanvasListener::onDisplayEvent" << endl;
	
	// Update frames
	++frames;
	if (frames > 30) {
		canvas->setAutomaticallyRefresh(false);
	}
	
	// Draw
	glClearColor(0.0, 1.0, 0.0, 1.0);
	canvas->clear();
	canvas->write("This is some text!");
	canvas->flush();
}

void FakeCanvasListener::onDragEvent(const CanvasEvent &event) {
	
	cout << event.state.x << " " << event.state.y << endl;
}

void FakeCanvasListener::onKeyEvent(const CanvasEvent &event) {
	
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

void createAndShowGUI() {
	
	Window *window;
	Canvas *canvas;
	FakeCanvasListener *listener;
	
	// Create window and canvas
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	
	// Create the listener
	listener = new FakeCanvasListener();
	listener->setCanvas(canvas);
	canvas->addListener(listener, CanvasEvent::BUTTON);
	canvas->addListener(listener, CanvasEvent::DISPLAY);
	canvas->addListener(listener, CanvasEvent::DRAG);
	canvas->addListener(listener, CanvasEvent::KEY);
	//canvas->setAutomaticallyRefresh(true);
	
	// Pack window
	window->setTitle("CanvasGLUT");
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

