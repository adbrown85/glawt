/*
 * Producer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Producer.hpp"


/** Prints the scene. */
void Producer::list(int command) {
	
	scene->print();
}


void Producer::copy(int command) {
	
	cout << "Producer::cmdCopy(int)" << endl;
}


void Producer::duplicate(int command) {
	
	cout << "Producer::cmdDuplicate(int)" << endl;
}


void Producer::cut(int command) {
	
	cout << "Producer::cmdCut(int)" << endl;
}


/** Opens a scene from an XML file.
 * 
 * @throw Exception if scene is NULL.
 */
void Producer::open(int command, const string &filename) {
	
	// Check for bad input
	if (scene == NULL) {
		throw Exception("[Producer] Cannot open file when scene is NULL.");
	}
	
	// Initialize
	BasicFactory::install();
	AdvancedFactory::install();
	scene->setRoot(Factory::create("translate"));
	
	// Open and prepare it
	scene->open(filename);
	scene->prepare();
}


void Producer::paste(int command) {
	
	cout << "Producer::cmdPaste(int)" << endl;
}


void Producer::save(int command) {
	
	cout << "Producer::cmdSave(int)" << endl;
}


void Producer::quit(int command) {
	
	exit(0);
}

