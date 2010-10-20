/*
 * Image.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Image.hpp"
#include "CanvasGTK.hpp"
#include <cassert>
#include <gtkmm/main.h>
#include <gtkmm/window.h>


/* Fake image for testing. */
class FakeImage : public Image {
public:
	FakeImage(const string &filename) : Image(filename) {}
	virtual GLchar* getData() const {return NULL;}
};

/* Test for Image. */
class ImageTest : public CanvasListener {
public:
	void setUp();
	void testFormat();
	void testGetData();
	void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventDisplay(const CanvasEvent &event);
private:
	Image *image;
	CanvasGTK *canvas;
	Gtk::Window *window;
};


/* Load the image. */
void ImageTest::setUp() {
	
	cout << "Setting up..." << endl;
	
	// Create image
	image = new FakeImage("../../textures/crate.jpg");
}


/* Makes sure the image determined if it uses alpha or not. */
void ImageTest::testFormat() {
	
	cout << "\nTesting format..." << endl;
	
	// Assert
	switch (image->getFormat()) {
	case GL_RGB:
		cout << "  GL_RGB" << endl;
		break;
	case GL_RGBA:
		cout << "  GL_RGBA" << endl;
		break;
	}
	assert(image->getFormat() == GL_RGB);
}


/* Displays the image in OpenGL. */
void ImageTest::testGetData() {
	
	cout << "\nTesting getData()..." << endl;
	
	// Create canvas
	canvas = new CanvasGTK();
	canvas->addListener(this, CanvasEvent::DISPLAY);
	
	// Pack
	window = new Gtk::Window();
	window->set_title("Image Test");
	window->add(*canvas);
	window->show_all();
	
	// Run
	Gtk::Main::run(*window);
}


/* Handles incoming canvas events. */
void ImageTest::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::DISPLAY:
		onCanvasEventDisplay(event);
		break;
	}
}


/* Handles an incoming canvas display event. */
void ImageTest::onCanvasEventDisplay(const CanvasEvent &event) {
	
	// Clear
	canvas->clear();
	
	// Draw pixels
	glDrawPixels(image->getWidth(),                         // width
	             image->getHeight(),                        // height
	             image->getFormat(),                        // format
	             GL_UNSIGNED_BYTE,                          // type
	             image->getData());                         // data
	
	// Flush
	canvas->flush();
}


/* Run the test */
int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::GL::init(argc, argv);
	ImageTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Image" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testFormat();
	test.testGetData();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Image" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

