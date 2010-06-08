/*
 * Uniform.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	Tester tester;
	
	// Initialize
	Gtk::Main kit(argc, argv);
	Gtk::GL::init(argc, argv);
	
	// Install tags
	BasicFactory::install();
	
	// Open
	tester.open("Uniform.xml");
	
	// Start
	tester.start();
	
	// Finish
	return 0;
}

