/*
 * Canvas.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Canvas.hpp"


/* Fake canvas with required implementations. */
class FakeCanvas : public Canvas {
public:
	FakeCanvas(int width, int height) : Canvas(width,height) {}
	virtual void flush() {}
	virtual GLuint getElapsedTime() {return 37;}
	virtual void refresh() {}
	void updateState(CanvasState state) {this->state = state;}
	virtual void primeStart() {}
	virtual void primeFinish() {}
	virtual void connectIdle() {}
	virtual void disconnectIdle() {}
	virtual void write(const string& text, int x, int y) {}
};

/* Fake canvas listener. */
class FakeCanvasListener : public CanvasListener {
public:
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas);
	virtual void onCanvasDragEvent(Canvas &canvas);
protected:
	void printState(const Canvas &canvas);
};

/* Prints an event to standard out. */
void FakeCanvasListener::printState(const Canvas &canvas) {
	cout << "  " << canvas.getState().x << " " << canvas.getState().y << endl;
	cout << "  " << canvas.getState().combo.trigger << " "
	             << canvas.getState().combo.modifier << " "
	             << canvas.getState().combo.action << endl;
}

/* Handles an init event from the canvas. */
void FakeCanvasListener::onCanvasInitEvent(Canvas &canvas) {
	cout << "Received INIT event..." << endl;
	printState(canvas);
}

/* Handles a display event from the canvas. */
void FakeCanvasListener::onCanvasDisplayEvent(Canvas &canvas) {
	cout << "Received DISPLAY event..." << endl;
	printState(canvas);
}

/* Handles a key event from the canvas. */
void FakeCanvasListener::onCanvasKeyEvent(Canvas &canvas) {
	cout << "Received KEY event..." << endl;
	printState(canvas);
}

/* Handles a button event from the canvas. */
void FakeCanvasListener::onCanvasButtonEvent(Canvas &canvas) {
	cout << "Received BUTTON event..." << endl;
	printState(canvas);
}

/* Handles a drag event from the canvas. */
void FakeCanvasListener::onCanvasDragEvent(Canvas &canvas) {
	cout << "Received DRAG event..." << endl;
	printState(canvas);
}

/* Test for canvas using fakes. */
class CanvasTest {
public:
	void setUp();
	void tearDown();
	void testEvent();
private:
	Canvas *canvas;
};

/* Creates the canvas. */
void CanvasTest::setUp() {
	
	canvas = new FakeCanvas(512, 512);
}

/* Deletes the canvas. */
void CanvasTest::tearDown() {
	
	delete canvas;
}

/* Tests that the listener receives the events. */
void CanvasTest::testEvent() {
	
	CanvasState state;
	
	// Add listeners
	canvas->addListener(new FakeCanvasListener());
	
	// Fire event
	state.x = 100;
	state.y = 200;
	state.combo.action = TOOLKIT_DOWN;
	state.combo.modifier = TOOLKIT_MOD_ALT;
	state.combo.trigger = TOOLKIT_LEFT_BUTTON;
	((FakeCanvas*)canvas)->updateState(state);
	canvas->fireEvent(CanvasEvent::BUTTON);
	
	// Fire event
	state.x = 50;
	state.y = 4000;
	state.combo.action = TOOLKIT_UP;
	state.combo.modifier = TOOLKIT_MOD_CONTROL;
	state.combo.trigger = TOOLKIT_RIGHT_BUTTON;
	((FakeCanvas*)canvas)->updateState(state);
	canvas->fireEvent(CanvasEvent::KEY);
}

int main(int argc, char *argv[]) {
	
	CanvasTest test;
	
	try {
		test.setUp();
		test.testEvent();
		test.tearDown();
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
	return 0;
}

