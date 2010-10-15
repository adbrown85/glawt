/*
 * Configuration.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Configuration.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/gl/init.h>
#include "CanvasGTK.hpp"


typedef int (*function_t)();

/* Test for Configuration */
class ConfigurationTest {
public:
	void setUp();
	void tearDown();
	void testGetMaxColorAttachments();
	void testGetMaxDrawBuffers();
protected:
	void testFunction(string message, function_t function);
private:
	CanvasGTK *canvas;
	Gtk::Window *window;
};


void ConfigurationTest::setUp() {
	
	canvas = new CanvasGTK();
	window = new Gtk::Window();
	window->add(*canvas);
	window->show_all();
	canvas->primeStart();
}


void ConfigurationTest::tearDown() {
	
	canvas->primeFinish();
	delete canvas;
	delete window;
}


void ConfigurationTest::testFunction(string message, function_t function) {
	
	cout << "  " << message << ": " << (*function)() << endl;
}


void ConfigurationTest::testGetMaxColorAttachments() {
	
	testFunction("MaxColorAttachments", &Configuration::getMaxColorAttachments);
}


void ConfigurationTest::testGetMaxDrawBuffers() {
	
	testFunction("MaxDrawBuffers", &Configuration::getMaxDrawBuffers);
}



int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::GL::init(argc, argv);
	ConfigurationTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Configuration" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testGetMaxColorAttachments();
	test.testGetMaxDrawBuffers();
	test.tearDown();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Configuration" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

