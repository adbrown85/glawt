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
	virtual void onCanvasInitEvent(const CanvasEvent &event);
	virtual void onCanvasDisplayEvent(const CanvasEvent &event);
	virtual void onCanvasKeyEvent(const CanvasEvent &event);
	virtual void onCanvasButtonEvent(const CanvasEvent &event);
	virtual void onCanvasDragEvent(const CanvasEvent &event);
protected:
	void printEvent(const CanvasEvent &event);
};

/* Prints an event to standard out. */
void FakeCanvasListener::printEvent(const CanvasEvent &event) {
	cout << "  " << event.type << endl;
	cout << "  " << event.state.x << " " << event.state.y << endl;
	cout << "  " << event.state.combo.trigger << " "
	             << event.state.combo.modifier << " "
	             << event.state.combo.action << endl;
}

/* Handles an init event from the canvas. */
void FakeCanvasListener::onCanvasInitEvent(const CanvasEvent &event) {
	cout << "Received INIT event..." << endl;
	printEvent(event);
}

/* Handles a display event from the canvas. */
void FakeCanvasListener::onCanvasDisplayEvent(const CanvasEvent &event) {
	cout << "Received DISPLAY event..." << endl;
	printEvent(event);
}

/* Handles a key event from the canvas. */
void FakeCanvasListener::onCanvasKeyEvent(const CanvasEvent &event) {
	cout << "Received KEY event..." << endl;
	printEvent(event);
}

/* Handles a button event from the canvas. */
void FakeCanvasListener::onCanvasButtonEvent(const CanvasEvent &event) {
	cout << "Received BUTTON event..." << endl;
	printEvent(event);
}

/* Handles a drag event from the canvas. */
void FakeCanvasListener::onCanvasDragEvent(const CanvasEvent &event) {
	cout << "Received DRAG event..." << endl;
	printEvent(event);
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

