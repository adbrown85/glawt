/*
 * Tester.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"
Scene Tester::scene;


/**
 * GLUT display callback.
 */
void Tester::display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	
	// Draw
	traverse(&scene.root);
	
	// Finish
	glFlush();
}


/**
 * Initializes the GLUT display.
 */
void Tester::initialize(string title) {
	
	char **argv;
	int argc=0;
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << title << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(512, 512);
	glutCreateWindow(title.c_str());
	
	// Set up viewport
	glViewport(0, 0, 512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.0, 100.0);
}


/**
 * Exits the %Tester on Escape key.
 */
void Tester::keyboard(unsigned char key,
                      int x,
                      int y) {
	
	switch (key) {
	case 27:
		exit(0);
	}
}


/**
 * Opens a scene.
 */
void Tester::open(string filename) {
	
	scene.open(filename);
	scene.prepare();
	scene.print();
}


/**
 * Starts the GLUT display.
 */
void Tester::start() {
	
	glutDisplayFunc(Tester::display);
	glutKeyboardFunc(Tester::keyboard);
	glutMainLoop();
}


/**
 * Applies and draws nodes.
 */
void Tester::traverse(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	
	// Drawable
	drawable = dynamic_cast<Drawable*>(node);
	if (drawable != NULL) {
		drawable->draw();
		traverseChildren(node);
		return;
	}
	
	// Applicable
	applicable = dynamic_cast<Applicable*>(node);
	if (applicable != NULL) {
		applicable->apply();
		traverseChildren(node);
		applicable->remove();
		return;
	}
	
	// Node
	traverseChildren(node);
}


/**
 * Traverses the children of a node.
 */
void Tester::traverseChildren(Node *node) {
	
	int count;
	vector<Node*> children;
	
	// Traverse each child
	children = node->getChildren();
	count = children.size();
	for (int i=0; i<count; ++i)
		traverse(children[i]);
}

