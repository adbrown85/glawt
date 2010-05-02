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
	} catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
}


/**
 * Allows nodes in graph to associate and finalize themselves.
 */
void Scene::prepare() {
	
	Node* node;
	queue<Node*> q;
	vector<Node*> children;
	vector<Node*>::iterator it;
	
	// Check for bad input
	if (root == NULL) {
		throw "[Scene] Cannot prepare empty scene.";
	}
	
	// Associate all the nodes
	q.push(root);
	while (!q.empty()) {
		node = q.front();
		node->associate();
		children = node->getChildren();
		for (it=children.begin(); it!=children.end(); ++it) {
			q.push(*it);
		}
		q.pop();
	}
	
	// Finalize all the nodes
	q.push(root);
	while (!q.empty()) {
		node = q.front();
		node->finalize();
		children = node->getChildren();
		for (it=children.begin(); it!=children.end(); ++it) {
			q.push(*it);
		}
		q.pop();
	}
}


/**
 * Prints the list of items stored.
 */
void Scene::print(const Node *node,
                  string indent) {
	
	vector<Node*>::const_iterator it;
	vector<Node*> children;
	
	// Check for bad input
	if (node == NULL)
		return;
	
	// Print node
	cout << indent << node << endl;
	
	// Print each child
	children = node->getChildren();
	for (it=children.begin(); it!=children.end(); ++it)
		print((*it), indent+"  ");
}


void Scene::setRoot(Node *node) {
	
	vector<Node*> children;
	vector<Node*>::iterator it;
	
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


