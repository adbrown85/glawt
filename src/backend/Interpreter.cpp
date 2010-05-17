/*
 * Interpreter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Interpreter.hpp"


/** Initializes the scene, loads the delegates, and adds commands from each.
 * 
 * @param scene Pointer to the Scene to work with.
 */
Interpreter::Interpreter(Scene *scene) {
	
	map<int,handler_0> handlersZero;
	map<int,handler_0>::iterator h0;
	map<int,handler_f> handlersFloat;
	map<int,handler_f>::iterator hf;
	map<int,handler_s> handlersString;
	map<int,handler_s>::iterator hs;
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


/** Cleans up the delegates. */
Interpreter::~Interpreter() {
	
	// Clean up
	for (size_t i=0; i<delegates.size(); i++)
		delete delegates[i];
}


/** Adds a callback that will be called when a command is issued. */
void Interpreter::addListener(int command,
                              interpreter_listener function) {
	
	listeners[command] = function;
}


/** Prints the commands. */
void Interpreter::print() {
	
	map<int,handler_0>::iterator h0;
	map<int,handler_f>::iterator hf;
	map<int,handler_s>::iterator hs;
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


/** Runs a command by calling a delegate's method.
 * 
 * @param command Enumerated type from 'Command.hpp'.
 */
void Interpreter::run(int command) {
	
	map<int,interpreter_listener>::iterator li;
	map<int,handler_0>::iterator hi;
	
	// Check for listener
	li = listeners.find(command);
	if (li != listeners.end())
		(li->second)(command);
	
	// Hand off to delegate
	hi = handlersZero.find(command);
	if (hi != handlersZero.end())
		(hi->second)(scene, command);
}


/** Runs a command by handing it off to a delegate.
 * 
 * @param command Enumerated type from 'Command.hpp'.
 * @param argument Argument to the command.
 */
void Interpreter::run(int command,
                      float argument) {
	
	map<int,interpreter_listener>::iterator li;
	map<int,handler_f>::iterator hi;
	
	// Check for listener
	li = listeners.find(command);
	if (li != listeners.end())
		(li->second)(command);
	
	// Hand off to delegate
	hi = handlersFloat.find(command);
	if (hi != handlersFloat.end())
		(hi->second)(scene, command, argument);
}


/** Runs a command by handing it off to a delegate.
 * 
 * @param command Enumerated type from 'Command.hpp'.
 * @param argument Argument to the command.
 */
void Interpreter::run(int command,
                      string argument) {
	
	map<int,interpreter_listener>::iterator li;
	map<int,handler_s>::iterator hi;
	
	// Check for listener
	li = listeners.find(command);
	if (li != listeners.end())
		(li->second)(command);
	
	// Hand off to delegate
	hi = handlersString.find(command);
	if (hi != handlersString.end())
		(hi->second)(scene, command, argument);
}

