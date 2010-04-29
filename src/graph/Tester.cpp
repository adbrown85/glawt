/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"
Scene Tester::scene;
map<string,callback_t> Tester::callbacks;


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
	traverse(scene.getRoot());
	
	// Finish
	glFlush();
}


callback_t Tester::findCallback(const string &name) {
	
	map<string,callback_t>::iterator it;
	
	it = callbacks.find(name);
	if (it != callbacks.end()) {
		return it->second;
	} else {
		return NULL;
	}
}


Scene* Tester::getScene() {
	
	return &scene;
}


/**
 * Initializes the GLUT display.
 */
void Tester::init(int argc,
                  char *argv[]) {
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);
	
	// Enable options
	glEnable(GL_CULL_FACE);
	
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


void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << FileUtility::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Open and prepare
	scene.open(filename);
	scene.prepare();
	scene.print();
}


void Tester::setCallback(const string &name,
                         callback_t callback) {
	
	callbacks[name] = callback;
}


/**
 * Starts the GLUT display.
 */
void Tester::start() {
	
	callback_t callback;
	
	callback = findCallback("display");
	if (callback == NULL) {
		glutDisplayFunc(Tester::display);
	} else {
		glutDisplayFunc(callback);
	}
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

