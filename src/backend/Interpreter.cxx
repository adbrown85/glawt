/*
 * Interpreter.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Interpreter.hpp"


void cutListener(int command) {
	
	cout << "void cutListener()" << endl;
}


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
	
	// Print commands
	interpreter.print();
	
	// Run
	cout << "\nRun commands:" << endl;
	interpreter.run(Command::COPY);
	interpreter.addListener(Command::CUT, &cutListener);
	interpreter.run(Command::CUT);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

