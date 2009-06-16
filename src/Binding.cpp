/*
 * Binding.cpp
 *     Tests Binding class.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Binding.hpp"
bool Binding::loaded=false;
std::map<int,std::string> Binding::keys;



/**
 * Initializes the required attributes for a binding.
 * 
 * @param trigger
 *     Button or key that triggers the command.
 * @param command
 *     Command to be issued.  From 'Command.h'.
 */
void Binding::init(int trigger,
                   int command) {
	
	// Set attributes
	trg = isCha ? toupper(trigger) : trigger;
	cmd = command;
	mod = 0;
	hasArg = false;
	hasSte = false;
	
	// Load names
	if (!loaded)
		names();
	loaded = true;
}



/**
 * Returns the name of a key or binding.
 */
std::string Binding::getName() const {
	
	std::map<int,std::string>::const_iterator n;
	std::string str;
	
	// Lookup and return name
	if (isCha && isalpha((char)trg))
		str = trg;
	else {
		n = keys.find(trg);
		if (n != keys.end())
			str = n->second;
		else
			str = "-";
	}
	return str;
}



/**
 * 
 */
std::string Binding::getModifierStr() const {
	
	std::string str="";
	
	// Lookup and return name
	switch (mod) {
		case 0                 : str = "None"; break;
		case GLUT_ACTIVE_CTRL  : str = "Ctrl"; break;
		case GLUT_ACTIVE_ALT   : str = "Alt"; break;
		case GLUT_ACTIVE_SHIFT : str = "Shift"; break;
	}
	return str;
}



/**
 * Prints the binding.
 */
std::ostream& operator<<(std::ostream& stream,
                         const Binding &b) {
	
	using namespace std;
	
	// Print
	if (b.hasModifier())
		stream << b.getModifierStr() << "+";
	stream << b.getName() << "\t\t";
	stream << b.getCommandStr();
	return stream;
}



/**
 * Simple test program.
 */
/*
#include <vector>
int main(int argc, char *argv[]) {
	
	using namespace std;
	Binding b1(GLUT_KEY_LEFT,
	           Command::CIRCLE_LEFT);
	Binding b2(GLUT_KEY_RIGHT,
	           Command::CIRCLE_RIGHT,
	           GLUT_ACTIVE_ALT);
	Binding b3(GLUT_KEY_UP,
	           Command::CIRCLE_UP,
	           GLUT_ACTIVE_SHIFT,
	           50.5);
	Binding b4('d',
	           Command::DESELECT);
	Binding b5('c',
	           Command::COPY,
	           GLUT_ACTIVE_CTRL);
	std::vector<Binding*> bins;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	bins.push_back(&b1);
	bins.push_back(&b2);
	bins.push_back(&b3);
	bins.push_back(&b4);
	bins.push_back(&b5);
	for (int i=0; i<bins.size(); i++)
		cout << *bins[i] << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
