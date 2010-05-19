/*
 * Gander.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Gander.hpp"


int main(int argc,
         char *argv[]) {
	
	Gander gander(argc, argv);
	
	try {
		gander.start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	return 0;
}

