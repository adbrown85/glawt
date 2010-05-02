/*
 * Scene.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scene.hpp"


/**
 * Creates and initializes a new scene.
 * 
 * @param filename
 */
Scene::Scene(const string &filename) {
	
	this->filename = filename;
	this->root = NULL;
}


Scene::~Scene() {
	
	if (root != NULL) {
		Node::destroy(root);
	}
}


/**
 * Opens a scene from a file.
 * 
 * @param filename Path to the file.
 */
void Scene::open(const string &filename) {
	
	// Parse and process tags
	try {
		cerr << "[Scene] Opening '" << filename << "'..." << endl;
		this->filename = filename;
		root = Factory::open(filename);
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
}


/**
 * Allows nodes in graph to associate and finalize themselves.
 */
void Scene::prepare() {
	
	if (root != NULL) {
		root->prepare();
	}
}


/**
 * Prints the list of items stored.
 */
void Scene::print() {
	
	if (root != NULL) {
		root->printTree();
	}
}


void Scene::setRoot(Node *node) {
	
	list<Node*> children;
	list<Node*>::iterator it;
	
	// Test for bad input
	if (node == NULL) {
		throw "[Scene] Cannot replace root with NULL node.";
	} else if (node->getChildrenSize() > 0) {
		throw "[Scene] Node replacing root cannot have children.";
	} else if (root == NULL) {
		throw "[Scene] Scene should be opened before replacing root";
	}
	
	// Move root's children to node's children
	children = root->getChildren();
	node->setChildren(children);
	for (it=children.begin(); it!=children.end(); ++it) {
		(*it)->setParent(node);
	}
	
	// Make node new root
	delete root;
	root = node;
}


