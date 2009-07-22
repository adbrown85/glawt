/*
 * Binding.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <cassert>
#include <cfloat>
#include <climits>
#include <iostream>
#include <vector>
#include "Binding.hpp"
using namespace std;



/**
 * Unit test for Binding.
 */
int main(int argc,
         char *argv[]) {
	
	Binding *binding;
	vector<Binding> bins;
	unsigned int number=5;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Check constructors
	cout << endl;
	cout << "Checking constructors:" << endl;
	bins.push_back(Binding(GLUT_KEY_LEFT, 0, Command::CIRCLE_LEFT));
	bins.push_back(Binding(GLUT_KEY_RIGHT, GLUT_ACTIVE_ALT, Command::CIRCLE_RIGHT));
	bins.push_back(Binding(GLUT_LEFT_BUTTON, GLUT_ACTIVE_SHIFT, Command::CIRCLE_UP));
	bins.push_back(Binding('\t', 0, Command::NEXT, 5.0f));
	bins.push_back(Binding('C', GLUT_ACTIVE_CTRL, Command::COPY));
	for (int i=0; i<bins.size(); i++)
		cout << "  " << bins[i] << endl;
	
	// Check argument
	cout << endl;
	cout << "Checking arguments:" << endl;
	binding = new Binding('E', 0, Command::COPY, &number, GLUT_DOWN);
	cout << "  " << binding->getArgument() << endl;
	assert(binding->getArgument() == number);
	delete binding;
	
	// Check maximums
	cout << endl;
	cout << "Checking maximums:" << endl;
	cout << "  Float: " << (unsigned int)FLT_MAX << endl;
	cout << "  Unsigned integer: " << UINT_MAX << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
