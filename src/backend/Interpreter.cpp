/*
 * Interpreter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Interpreter.hpp"



/**
 * Initializes the scene, loads the delegates, and adds commands from each.
 * 
 * @param scene
 *     Pointer to the Scene to work with.
 */
Interpreter::Interpreter(Scene *scene) {
	
	map<int,void(*)(Scene*,int)> handlersZero;
	map<int,void(*)(Scene*,int)>::iterator h0;
	map<int,void(*)(Scene*,int,float)> handlersFloat;
	map<int,void(*)(Scene*,int,float)>::iterator hf;
	map<int,void(*)(Scene*,int,string)> handlersString;
	map<int,void(*)(Scene*,int,string)>::iterator hs;
	vector<Delegate*>::iterator di;
	
	// Initialize
	this->scene = scene;
	
	// Load delegates
	delegates.push_back(new Cameraman());
	delegates.push_back(new Compositor());
	delegates.push_back(new Director());
	delegates.push_back(new Grip());
	delegates.push_back(new Producer());
	
	// Add commands from each delegate {
	for (di=delegates.begin(); di!=delegates.end(); di++) {
		handlersZero = (*di)->getHandlersZero();
		for (h0=handlersZero.begin(); h0!=handlersZero.end(); ++h0)
			this->handlersZero[h0->first] = h0->second;
		handlersFloat = (*di)->getHandlersFloat();
		for (hf=handlersFloat.begin(); hf!=handlersFloat.end(); ++hf)
			this->handlersFloat[hf->first] = hf->second;
		handlersString = (*di)->getHandlersString();
		for (hs= handlersString.begin(); hs!=handlersString.end(); ++hs)
			this->handlersString[hs->first] = hs->second;
	}
}



/**
 * Cleans up the delegates.
 */
Interpreter::~Interpreter() {
	
	// Clean up
	for (size_t i=0; i<delegates.size(); i++)
		delete delegates[i];
}



/**
 * Prints the commands.
 */
void Interpreter::print() {
	
	map<int,void(*)(Scene*,int)>::iterator h0;
	map<int,void(*)(Scene*,int,float)>::iterator hf;
	map<int,void(*)(Scene*,int,string)>::iterator hs;
	string commandName;
	
	// Get commands
	cout << "Zero-argument handlers: " << endl;
	for (h0=handlersZero.begin(); h0!=handlersZero.end(); ++h0)
		cout << "  " << Command::getName(h0->first) << endl;
	cout << "Float-argument handlers: " << endl;
	for (hf=handlersFloat.begin(); hf!=handlersFloat.end(); ++hf)
		cout << "  " << Command::getName(hf->first) << endl;
	cout << "String-argument handlers: " << endl;
	for (hs=handlersString.begin(); hs!=handlersString.end(); ++hs)
		cout << "  " << Command::getName(hf->first) << endl;
}



/**
 * Runs a command by calling a delegate's method.
 * 
 * @param command
 *     Enumerated type from 'Command.hpp'.
 */
void Interpreter::run(int command) {
	
	map<int,void(*)(Scene*,int)>::iterator hi;
	
	// Hand off to delegate
	hi = handlersZero.find(command);
	if (hi != handlersZero.end())
		(hi->second)(scene, command);
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
	
	map<int,void(*)(Scene*,int,float)>::iterator hi;
	
	// Hand off to delegate
	hi = handlersFloat.find(command);
	if (hi != handlersFloat.end())
		(hi->second)(scene, command, argument);
}



/**
 * Runs a command by handing it off to a delegate.
 * 
 * @param command
 *     Enumerated type from 'Command.hpp'.
 * @param argument
 *     Argument to the command.
 */
void Interpreter::run(int command, string argument) {
	
	map<int,void(*)(Scene*,int,string)>::iterator hi;
	
	// Hand off to delegate
	hi = handlersString.find(command);
	if (hi != handlersString.end())
		(hi->second)(scene, command, argument);
}



/**
 * Simple test program.
 */
/*
int main(int argc, char *argv[]) {
	
	Scene scene;
	Interpreter interpreter(&scene);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	interpreter.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
