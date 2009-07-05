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
	
	// Set type
	type = "Producer";
	
	// Add zero-argument handlers
	handlersZero[Command::COPY] = &Producer::copy;
	handlersZero[Command::CUT] = &Producer::cut;
	handlersZero[Command::DUPLICATE] = &Producer::duplicate;
	handlersZero[Command::EXIT] = &Producer::quit;
	handlersZero[Command::PASTE] = &Producer::paste;
	handlersZero[Command::SAVE] = &Producer::save;
	
	// Add string-argument handlers
	handlersString[Command::OPEN] = &Producer::open;
}



void Producer::copy(Scene *scene, int command) {
	
	std::cout << "Producer::cmdCopy(Scene*,int)" << std::endl;
}



void Producer::duplicate(Scene *scene, int command) {
	
	std::cout << "Producer::cmdDuplicate(Scene*,int)" << std::endl;
}



void Producer::cut(Scene *scene, int command) {
	
	std::cout << "Producer::cmdCut(Scene*,int)" << std::endl;
}



void Producer::open(Scene *scene, int command, string filename) {
	
	std::cout << "Opening " << filename << std::endl;
}



void Producer::paste(Scene *scene, int command) {
	
	std::cout << "Producer::cmdPaste(Scene*,int)" << std::endl;
}



void Producer::save(Scene *scene, int command) {
	
	std::cout << "Producer::cmdSave(Scene*,int)" << std::endl;
}



void Producer::quit(Scene *scene, int command) {
	
	exit(0);
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
