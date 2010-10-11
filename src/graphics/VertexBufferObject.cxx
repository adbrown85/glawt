/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Toolkit.hpp"
#include "WindowFactory.hpp"
#include "CanvasFactory.hpp"
#include "VertexBufferObject.hpp"


/* CanvasListener. */
class FakeCanvasListener : public CanvasListener {
public:
	virtual void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventDisplay();
	void setCanvas(Canvas *canvas) {this->canvas = canvas;}
private:
	Canvas *canvas;
};

/* Handles canvas events. */
void FakeCanvasListener::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::DISPLAY:
		onCanvasEventDisplay();
	}
}

/* Handles a canvas display event. */
void FakeCanvasListener::onCanvasEventDisplay() {
	
	glClearColor(0.0, 1.0, 1.0, 1.0);
	canvas->flush();
}

/* Test for VertexBufferObject. */
class VertexBufferObjectTest {
public:
	void setUp();
//	void testAllocate();
private:
	VertexBufferObject *vbo;
	Window *window;
	Canvas *canvas;
	FakeCanvasListener *listener;
};

/* Initializes the test. */
void VertexBufferObjectTest::setUp() {
	
	window = WindowFactory::create();
	canvas = CanvasFactory::create(512, 512);
	listener = new FakeCanvasListener();
	listener->setCanvas(canvas);
	canvas->addListener(listener, CanvasEvent::DISPLAY);
	window->setTitle("VertexBufferObject Test");
	window->add(canvas);
	window->show();
	
	// Initialize
	vbo = new VertexBufferObject();
	ErrorChecker::check("After vertex buffer object.");
	list<VertexAttribute> attribs;
	attribs.push_back(VertexAttribute("MCVertex", 3));
	attribs.push_back(VertexAttribute("TexCoord0", 3));
	vbo->allocate(GL_STATIC_DRAW, 3, attribs);
	cerr << "Size: " << vbo->getSize() << endl;
	vbo->put(-0.5, +0.5, 0); // 1
	vbo->put( 0.0,  0.1, 0);
	vbo->put(-0.5, -0.5, 0); // 2
	vbo->put( 0.0,  0.0, 0);
	vbo->put(+0.5, +0.5, 0); // 3
	vbo->put( 1.0,  1.0, 0);
	vbo->put(0.0, 0.0, 0.0); // Should throw exception!!
	
	window->run();
}

/* Runs the test. */
int main(int argc, char **argv) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectTest test;
	
	try {
		test.setUp();
	} catch (Exception &e) {
		cerr << e.getMessage() << endl;
	}
	
}
