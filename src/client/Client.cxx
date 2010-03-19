/*
 * Client.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "Client.hpp"


int main(int argc,
         char *argv[]) {
	
	Client client;
	
	try {
		// Start the client
		client.parse(argc, argv);
		client.start();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

