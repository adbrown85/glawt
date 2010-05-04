/*
 * Instance.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Test
	BasicFactory::install();
	AdvancedFactory::install();
	Window::init(argc, argv);
	Tester::open("Instance.xml");
	Tester::start();
	return 0;
}

