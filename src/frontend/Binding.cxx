/*
 * Binding.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cassert>
#include <cfloat>
#include <climits>
#include <iostream>
#include "Binding.hpp"
using namespace std;


/* Test for Binding. */
class BindingTest {
public:
	void setUp();
	void testArgument();
	void testPrint();
private:
	list<Binding> bindings;
};

/* Create a few bindings. */
void BindingTest::setUp() {
	
	Combo combo;
	
	cout << "Setting up..." << endl;
	
	// Left arrow
	combo.trigger = CANVAS_KEY_LEFT;
	combo.modifier = CANVAS_MOD_CONTROL;
	combo.action = CANVAS_DOWN;
	bindings.push_back(Binding(combo, Command::CIRCLE_LEFT));
	
	// Right arrow
	combo.trigger = CANVAS_ESCAPE;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	bindings.push_back(Binding(combo, Command::EXIT));
}

/* Print all of them. */
void BindingTest::testPrint() {
	
	list<Binding>::iterator it;
	
	cout << "\nTesting print..." << endl;
	
	// Print
	for (it=bindings.begin(); it!=bindings.end(); ++it) {
		cout << "  " << it->toString() << endl;
	}
}

/* Make sure pointer arguments are dereferenced. */
void BindingTest::testArgument() {
	
	Binding *binding;
	Combo combo;
	unsigned int number=5;
	
	cout << "\nTesting argument..." << endl;
	
	// Make binding
	combo.trigger = 'Q';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	binding = new Binding(combo, Command::COPY, &number);
	
	// Get the argument
	if (binding->hasArgument()) {
		cout << "  " << binding->getArgument() << endl;
		assert(binding->getArgument() == number);
	}
	delete binding;
}


/* Run the test. */
int main(int argc, char *argv[]) {
	
	BindingTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		test.setUp();
		test.testPrint();
		test.testArgument();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Binding" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

