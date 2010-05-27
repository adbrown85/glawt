/*
 * MouseDragHelper.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <GL/glut.h>
#include <iostream>
#include <map>
#include "Binding.hpp"
#include "Command.hpp"
#include "Delegate.hpp"
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
	
	Delegate *delegate;
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
	delegate = new Delegate(scene);
	mdh = new MouseDragHelper(delegate);
	addBindings(bins);
	
	// Test install
	glutInit(&argc, argv);
	mdh->setBindings(bins);
	mdh->install();
	mdh->print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MouseDragHelper" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

