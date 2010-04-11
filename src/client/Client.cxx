/*
 * Client.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Client.hpp"


int main(int argc,
         char *argv[]) {
	
	Client client(argc, argv);
	
	try {
		client.start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

