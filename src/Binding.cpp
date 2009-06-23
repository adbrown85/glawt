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
map<int,string> Binding::nams;



float Binding::getArgument() const {
	
	if (argi != NULL)
		return static_cast<float>(*argi);
	else
		return argf;
}



/**
 * 
 */
string Binding::getModifierStr() const {
	
	string str="";
	
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
 * Returns the name of a key or binding.
 */
string Binding::getTriggerStr() const {
	
	map<int,string>::const_iterator n;
	string str;
	
	// Lookup and return name
	if (isCharacter() && isalpha((char)trg))
		str = trg;
	else {
		n = nams.find(trg);
		if (n != nams.end())
			str = n->second;
		else
			str = "-";
	}
	return str;
}



bool Binding::hasDrag() const {
	
	return (sta == 'x' || sta == 'y');
}



/**
 * Initializes the required attributes for a binding.
 */
void Binding::init(int trg, int mod, int cmd, int sta) {
	
	// Load names
	if (!loaded)
		names();
	loaded = true;
	
	// Set attributes
	this->trg = isCharacter(trg) ? toupper(trg) : trg;
	this->mod = mod;
	this->cmd = cmd;
	this->sta = sta;
	hasArg = false;
}



/**
 * Initializes the required attributes for a binding.
 */
void Binding::init(int trg, int mod, int cmd, int sta, float arg) {
	
	// Set attributes
	init(trg, mod, cmd, sta);
	this->argf = arg;
	this->argi = NULL;
	hasArg = true;
}



/**
 * Initializes the required attributes for a binding.
 */
void Binding::init(int trg, int mod, int cmd, int sta, int *arg) {
	
	// Set attributes
	init(trg, mod, cmd, sta);
	this->argf = 0.0;
	this->argi = arg;
	hasArg = true;
}



/**
 * Trigger is a character if it's not listed in the 'nams' map.
 */
bool Binding::isCharacter(int trg) {
	
	map<int,string>::const_iterator ni;
	
	// Check exceptions
	if (trg == '\t')
		return true;
	
	// Check if in names
	ni = nams.find(trg);
	return ni == nams.end();
}



/**
 * Prints the binding.
 */
std::ostream& operator<<(std::ostream& stream,
                         const Binding &b) {
	
	string str;
	
	// Format
	if (b.hasModifier())
		str = b.getModifierStr() + "+";
	str += b.getTriggerStr();
	
	// Print
	stream << std::setw(15) << std::left << str;
	stream << b.getCommandStr();
	return stream;
}



/**
 * Simple test program.
 */
/*
#include <vector>
using std::vector;
int main(int argc, char *argv[]) {
	
	using namespace std;
	Binding b1(GLUT_KEY_LEFT, 0, Command::CIRCLE_LEFT);
	Binding b2(GLUT_KEY_RIGHT, GLUT_ACTIVE_ALT, Command::CIRCLE_RIGHT);
	Binding b3(GLUT_LEFT_BUTTON, GLUT_ACTIVE_SHIFT, Command::CIRCLE_UP);
	Binding b4('D', 0, Command::DESELECT, 5.0f);
	Binding b5('C', GLUT_ACTIVE_CTRL, Command::COPY);
	vector<Binding*> bins;
	
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
	for (int i=0; i<bins.size(); i++) {
		cout << *bins[i] << endl;
		// cout << bins[i]->getState() << endl;
	}
	cout << GLUT_DOWN << endl;
	cout << GLUT_UP << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
