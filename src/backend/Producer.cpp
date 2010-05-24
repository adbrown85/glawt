/*
 * Producer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Producer.hpp"


/** Adds the commands this delegate supports and sets up handlers. */
Producer::Producer() {
	
	// Set type
	type = "Producer";
	
	// Add zero-argument handlers
	handlersZero[Command::EXIT] = &Producer::quit;
	handlersZero[Command::LIST] = &Producer::list;
	//handlersZero[Command::COPY] = &Producer::copy;
	//handlersZero[Command::CUT] = &Producer::cut;
	//handlersZero[Command::DUPLICATE] = &Producer::duplicate;
	//handlersZero[Command::PASTE] = &Producer::paste;
	//handlersZero[Command::SAVE] = &Producer::save;
	
	// Add string-argument handlers
	handlersString[Command::OPEN] = &Producer::open;
}


void Producer::list(Scene *scene, Canvas *canvas, int command) {
	
	scene->print();
}


void Producer::copy(Scene *scene, Canvas *canvas, int command) {
	
	cout << "Producer::cmdCopy(int)" << endl;
}


void Producer::duplicate(Scene *scene, Canvas *canvas, int command) {
	
	cout << "Producer::cmdDuplicate(int)" << endl;
}


void Producer::cut(Scene *scene, Canvas *canvas, int command) {
	
	cout << "Producer::cmdCut(int)" << endl;
}


/** Opens a scene from an XML file.
 * 
 * @throws Exception if scene is NULL.
 */
void Producer::open(Scene *scene,
                    Canvas *canvas,
                    int command,
                    const string &filename) {
	
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


void Producer::paste(Scene *scene, Canvas *canvas, int command) {
	
	cout << "Producer::cmdPaste(int)" << endl;
}


void Producer::save(Scene *scene, Canvas *canvas, int command) {
	
	cout << "Producer::cmdSave(int)" << endl;
}


void Producer::quit(Scene *scene, Canvas *canvas, int command) {
	
	exit(0);
}

