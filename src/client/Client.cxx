/*
 * Client.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
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

