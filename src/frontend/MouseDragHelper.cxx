/*
 * MouseDragHelper.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <GL/glut.h>
#include <iostream>
#include <map>
#include "Binding.hpp"
#include "Command.hpp"
#include "Interpreter.hpp"
#include "MouseDragHelper.hpp"
#include "Scene.hpp"
using namespace std;



void addBindings(multimap<int,Binding> &bins) {
	
	int key=GLUT_LEFT_BUTTON;
	
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      GLUT_ACTIVE_ALT,
	                                      Command::GRAB,
	                                      0.0f,
	                                      GLUT_DOWN)));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      GLUT_ACTIVE_ALT,
	                                      Command::MANIPULATE,
	                                      1.0f,
	                                      GLUT_DOWN)));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      0,
	                                      Command::CIRCLE_X,
	                                      1.0f,
	                                      'y')));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      0,
	                                      Command::CIRCLE_Y,
	                                      1.0f,
	                                      'x')));
}



/**
 * Unit test for MouseDragHelper.
 */
int main(int argc,
         char *argv[]) {
	
	Interpreter *interpreter;
	MouseDragHelper *mdh;
	Scene *scene;
	multimap<int,Binding> bins;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MouseDragHelper" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	scene = new Scene();
	interpreter = new Interpreter(scene);
	mdh = new MouseDragHelper(interpreter);
	addBindings(bins);
	
	// Test install
	glutInit(&argc, argv);
	mdh->initialize(bins);
	mdh->install(scene);
	mdh->print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MouseDragHelper" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
