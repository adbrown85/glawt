/*
 * Producer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Producer.hpp"


/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Producer::Producer() {
	
	// Set type
	type = "Producer";
	
	// Add zero-argument handlers
	handlersZero[Command::COPY] = &Producer::copy;
	handlersZero[Command::CUT] = &Producer::cut;
	handlersZero[Command::DUPLICATE] = &Producer::duplicate;
	handlersZero[Command::EXIT] = &Producer::quit;
	handlersZero[Command::PASTE] = &Producer::paste;
	handlersZero[Command::SAVE] = &Producer::save;
	handlersZero[Command::LIST] = &Producer::list;
	
	// Add string-argument handlers
	handlersString[Command::OPEN] = &Producer::open;
}


void Producer::list(Scene *scene,
                    int command) {
	
	scene->print();
}


void Producer::copy(Scene *scene,
                    int command) {
	
	cout << "Producer::cmdCopy(Scene*,int)" << endl;
}


void Producer::duplicate(Scene *scene,
                         int command) {
	
	cout << "Producer::cmdDuplicate(Scene*,int)" << endl;
}


void Producer::cut(Scene *scene,
                   int command) {
	
	cout << "Producer::cmdCut(Scene*,int)" << endl;
}


/**
 * Opens a scene from an XML file.
 * 
 * @param scene
 * @param command
 * @param filename
 */
void Producer::open(Scene *scene,
                    int command,
                    string filename) {
	
	// Open the scene
	BasicFactory::install();
	AdvancedFactory::install();
	scene->open(filename);
	
	// Prepare it
	scene->setRoot(Factory::create("translate"));
	scene->prepare();
}


void Producer::paste(Scene *scene,
                     int command) {
	
	cout << "Producer::cmdPaste(Scene*,int)" << endl;
}


void Producer::save(Scene *scene,
                    int command) {
	
	cout << "Producer::cmdSave(Scene*,int)" << endl;
}


void Producer::quit(Scene *scene,
                    int command) {
	
	exit(0);
}

