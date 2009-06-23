/*
 * Interpreter.cpp
 *     Interprets directives and issues commands for Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Interpreter.hpp"



Interpreter::Interpreter(Scene *scene) {
	
	std::vector<int> cmds;
	std::vector<int>::iterator c;
	std::vector<Delegate*>::iterator d;
	
	// Initialize
	this->scene = scene;
	
	// Load delegates
	load();
	for (d=dels.begin(); d!=dels.end(); d++)
		(*d)->setScene(scene);
	
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
		          << std::setw(10) << h->second->getType() << " <- " 
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
	
	map<int,Delegate*>::iterator hi;
	
	// Hand off to delegate
	hi = hans.find(command);
	if (hi != hans.end())
		hi->second->run(command);
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
	
	map<int,Delegate*>::iterator hi;
	
	// Hand off to delegate
	hi = hans.find(command);
	if (hi != hans.end())
		hi->second->run(command, argument);
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
	inter.run(Command::HIDE);
	inter.run(Command::SELECT_ALL);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
