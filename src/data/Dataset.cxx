/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include <GL/glut.h>
#include "Dataset.hpp"


int main(int argc,
         char *argv[]) {
	
	unsigned char byteValue;
	GLenum type;
	float floatValue;
	Index index;
	short shortValue;
	string filename;
	
	// Handle arguments
	if (argc == 1)
		filename = "../../textures/bear.vlb";
	else if (argc == 5) {
		filename = argv[1];
		index = Index(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	}
	else {
		cerr << "Usage: " << argv[0] 
		     << " [<filename>] [i j k]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create and print existing
		Dataset dataset(filename);
		dataset.print();
		dataset.print(index);
		
		// Assign new value
		cout << endl;
		cout << "Assigning new value..." << endl;
		byteValue = 200;
		shortValue = 215;
		floatValue = 230.5;
		type = dataset.getType();
		switch (type) {
			case GL_UNSIGNED_BYTE:
				dataset.set(index, &byteValue, type);
				break;
			case GL_SHORT:
				dataset.set(index, &shortValue, type);
				break;
			case GL_FLOAT:
				dataset.set(index, &floatValue, type);
				break;
		}
		dataset.print(index);
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

