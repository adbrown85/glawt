/*
 * Interpreter.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Interpreter.hpp"


int main(int argc,
         char *argv[]) {
	
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

