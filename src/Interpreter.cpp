/*
 * Interpreter.cpp
 *     Interprets directives and issues commands for Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Interpreter.hpp"



Interpreter::Interpreter(Scene *scene,
                         State *state) {
	
	std::vector<int> cmds;
	std::vector<int>::iterator c;
	std::vector<Delegate*>::iterator d;
	
	// Load delegates
	load();
	for (d=dels.begin(); d!=dels.end(); d++) {
		(*d)->setScene(scene);
		(*d)->setState(state);
	}
	
	// Add commands from each delegate {
	for (d=dels.begin(); d!=dels.end(); d++) {
		cmds = (*d)->getCommands();
		for (c=cmds.begin(); c!=cmds.end(); c++) {
			this->cmds.push_back(*c);
			this->hans[*c] = *d;
		}
	}
}



/**
 * Cleans up the delegates.
 */
Interpreter::~Interpreter() {
	
	// Clean up
	for (int i=0; i<dels.size(); i++)
		delete dels[i];
}



/**
 * Prints the commands.
 */
void Interpreter::print() {
	
	std::map<int,Delegate*>::iterator h;
	
	// Get commands
	std::cout << "Interpreter handlers: " << std::endl;
	for (h=hans.begin(); h!=hans.end(); h++) {
		std::cout << "  "
		          << setw(10) << h->second->getType() << " <- " 
		          << Command::getName(h->first) << std::endl;
		hans[h->first] = h->second;
	}
}



/**
 * Runs a command by handing it off to a delegate.
 * 
 * @param command
 *     Enumerated type from 'Command.hpp'.
 */
void Interpreter::run(int command) {
	
	// Hand off to delegate
	hans[command]->run(command);
}



/**
 * Runs a command by handing it off to a delegate.
 * 
 * @param command
 *     Enumerated type from 'Command.hpp'.
 * @param argument
 *     Argument to the command.
 */
void Interpreter::run(int command, float argument) {
	
	// Hand off to delegate
	hans[command]->run(command, argument);
}



/**
 * Runs a command by handing it off to a delegate.
 * 
 * @param command
 *     Enumerated type from 'Command.hpp'.
 * @param arg1
 *     First argument to the command.
 * @param arg2
 *     Second argument to the command.
 */
void Interpreter::run(int command, float arg1, float arg2) {
	
	// Hand off to delegate
	hans[command]->run(command, arg1, arg2);
}



/**
 * Simple test program.
 */
/*
int main(int argc, char *argv[]) {
	
	Scene scene;
	State state;
	Interpreter inter(&scene, &state);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	inter.run(Command::COPY);
	inter.run(Command::ZOOM_IN);
	inter.run(Command::HIDE);
	inter.run(Command::SELECT_ALL);
	inter.run(Command::ROTATE_X_MINUS);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
