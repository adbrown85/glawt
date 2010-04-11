/*
 * Mouse.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <GL/glut.h>
#include <iostream>
#include "Interpreter.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * Unit test for Mouse.
 */
int main(int argc,
         char *argv[]) {
	
	Scene scene;
	Interpreter interpreter(&scene);
	Mouse mouse(&interpreter);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Mouse" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test install
	glutInit(&argc, argv);
	mouse.install(&scene);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Mouse" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

