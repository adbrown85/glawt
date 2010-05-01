/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"
Scene Tester::scene;
Traverser *Tester::traverser;


/**
 * GLUT display callback.
 */
void Tester::display(void) {
	
	// Clear
	Window::clear();
	
	// Draw
	Window::applyView();
	traverser->start();
	
	// Finish
	Window::flush();
}


void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << FileUtility::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	Window::create(filename);
	Window::setDisplay(&display);
	
	// Open and prepare
	scene.open(filename);
	scene.prepare();
	scene.print();
}


void Tester::start() {
	
	traverser = new Traverser(&scene);
	Window::start();
}


/**
 * Applies and draws nodes.
 */
/*
void Tester::traverse(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	
	// Drawable
	drawable = dynamic_cast<Drawable*>(node);
	if (drawable != NULL) {
		drawable->draw();
		traverser->traverseChildren(node);
		return;
	}
	
	// Applicable
	applicable = dynamic_cast<Applicable*>(node);
	if (applicable != NULL) {
		applicable->apply();
		traverser->traverseChildren(node);
		applicable->remove();
		return;
	}
	
	// Node
	traverser->traverseChildren(node);
}
*/


/**
 * Traverses the children of a node.
 */
/*
void Tester::traverseChildren(Node *node) {
	
	int count;
	vector<Node*> children;
	
	// Traverse each child
	children = node->getChildren();
	count = children.size();
	for (int i=0; i<count; ++i)
		traverse(children[i]);
}
*/

