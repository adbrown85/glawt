/*
 * Producer.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Producer.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Producer::Producer() {
	
	std::map<int,void(Producer::*)()>::iterator h;
	
	// Set type
	type = "Producer";
	
	// Add handlers
	hans[Command::COPY] = &Producer::cmdCopy;
	hans[Command::CUT] = &Producer::cmdCut;
	hans[Command::DUPLICATE] = &Producer::cmdDuplicate;
	hans[Command::EXIT] = &Producer::cmdExit;
	hans[Command::OPEN] = &Producer::cmdOpen;
	hans[Command::PASTE] = &Producer::cmdPaste;
	hans[Command::SAVE] = &Producer::cmdSave;
	
	// Copy commands
	for (h=hans.begin(); h!=hans.end(); h++)
		cmds.push_back(h->first);
}



/**
 * Interprets a command.
 */
void Producer::run(int command) {
	
	void (Producer::*method)();
	
	// Filter command to correct method
	method = hans[command];
	(this->*method)();
}



void Producer::cmdCopy() {
	
	std::cout << "Producer::cmdCopy()" << std::endl;
}



void Producer::cmdDuplicate() {
	
	std::cout << "Producer::cmdDuplicate()" << std::endl;
}



void Producer::cmdCut() {
	
	std::cout << "Producer::cmdCut()" << std::endl;
}



void Producer::cmdExit() {
	
	exit(0);
}



void Producer::cmdOpen() {
	
	std::cout << "Producer::cmdOpen()" << std::endl;
}



void Producer::cmdPaste() {
	
	std::cout << "Producer::cmdPaste()" << std::endl;
}



void Producer::cmdSave() {
	
	std::cout << "Producer::cmdSave()" << std::endl;
}



/**
 * Simple test program.
 */
/*
int main(int argc, char *argv[]) {
	
	using namespace std;
	Scene scene;
	State state;
	Producer producer(&scene, &state);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	producer.run(Command::BOB_DOWN);
	producer.run(Command::BOB_UP);
	producer.run(Command::CUT);
	producer.run(Command::TRANSLATE_X_MINUS);
	producer.run(Command::SAVE);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
