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
	virtual void refresh() {}
	void updateState(CanvasState state) {this->state = state;}
	virtual void primeStart() {}
	virtual void primeFinish() {}
	virtual void setAutomaticallyRefresh(bool automaticRefresh) {}
	virtual void write(const string &text, int x=15, int y=30) {}
};

/* Fake canvas listener. */
class FakeCanvasListener : public CanvasListener {
public:
	FakeCanvasListener(const string &name) {this->name = name;}
	virtual void onCanvasEvent(const CanvasEvent &event) {
		cout << name << " received event..." << endl;
		cout << "  " << event.type << endl;
		cout << "  " << event.state.x << " " << event.state.y << endl;
		cout << "  " << event.state.combo.trigger << " "
		             << event.state.combo.modifier << " "
		             << event.state.combo.action << endl;
	}
private:
	string name;
};

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
	canvas->addListener(new FakeCanvasListener("mous"), CanvasEvent::BUTTON);
	canvas->addListener(new FakeCanvasListener("keyb"), CanvasEvent::KEY);
	canvas->addListener(new FakeCanvasListener("pain"), CanvasEvent::DISPLAY);
	canvas->addListener(new FakeCanvasListener("main"), CanvasEvent::SETUP);
	
	// Fire event
	state.x = 100;
	state.y = 200;
	state.combo.action = CANVAS_DOWN;
	state.combo.modifier = CANVAS_MOD_ALT;
	state.combo.trigger = CANVAS_LEFT_BUTTON;
	((FakeCanvas*)canvas)->updateState(state);
	canvas->fireEvent(CanvasEvent::BUTTON);
	
	// Fire event
	state.x = 50;
	state.y = 4000;
	state.combo.action = CANVAS_UP;
	state.combo.modifier = CANVAS_MOD_CONTROL;
	state.combo.trigger = CANVAS_RIGHT_BUTTON;
	((FakeCanvas*)canvas)->updateState(state);
	canvas->fireEvent(CanvasEvent::KEY);
}


int main(int argc, char *argv[]) {
	
	CanvasTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Canvas" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		test.setUp();
		test.testEvent();
		test.tearDown();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Canvas" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

