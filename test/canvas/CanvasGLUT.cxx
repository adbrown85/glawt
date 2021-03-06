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
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas);
	virtual void onCanvasDragEvent(Canvas &canvas);
private:
	GLuint frames;
};

void FakeCanvasListener::onCanvasInitEvent(Canvas &canvas) {
	
	cout << "Initialize!" << endl;
}

void FakeCanvasListener::onCanvasDisplayEvent(Canvas &canvas) {
	
	cout << "FakeCanvasListener::onDisplayEvent" << endl;
	
	// Update frames
	++frames;
	if (frames > 30) {
		canvas.setAutomaticallyRefresh(false);
	}
	
	// Draw
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	canvas.write("This is some text!");
}

void FakeCanvasListener::onCanvasKeyEvent(Canvas &canvas) {
	
	switch (canvas.getState().combo.trigger) {
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
		if (isprint((char)canvas.getState().combo.trigger))
			cout << (char)canvas.getState().combo.trigger << endl;
		else
			cout << "Non-printable character." << endl;
	}
}

void FakeCanvasListener::onCanvasButtonEvent(Canvas &canvas) {
	
	switch (canvas.getState().combo.trigger) {
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

void FakeCanvasListener::onCanvasDragEvent(Canvas &canvas) {
	
	cout << canvas.getState().x << " " << canvas.getState().y << endl;
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

