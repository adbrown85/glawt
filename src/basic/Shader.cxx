/*
 * Shader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"
#include "Window.hpp"
#include "BasicFactory.hpp"
Node *program, *shader;


int main(int argc,
         char *argv[]) {
	
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	Window::init(argc, argv);
	Window::create("Shader");
	
	// Test
	try {
		BasicFactory::install();
		program = Factory::create("program");
		shader = Factory::create("shader file='Shader.frag'");
		program->addChild(shader);
		program->associate();
		shader->associate();
		cout << "Shader type: " << ((Shader*)shader)->getType() << endl;
		((Shader*)shader)->list();
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

