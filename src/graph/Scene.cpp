/*
 * Scene.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scene.hpp"


/**
 * Creates and initializes a new scene.
 */
Scene::Scene() {
	
	this->root = new Node();
}


/**
 * Destroys all the nodes in the scene.
 */
Scene::~Scene() {
	
	Node::destroy(root);
}


/**
 * Associate all the nodes in the scene.
 */
void Scene::associate(Node *node) {
	
	Node::iterator it;
	
	// Check if sealed
	if (node->isSealed())
		return;
	
	// Finalize nodes in correct order
	node->associate();
	for (it=node->begin(); it!=node->end(); ++it)
		associate(*it);
	node->associateAfter();
}


/**
 * Finalize all the nodes in the scene.
 */
void Scene::finalize(Node *node) {
	
	Node::iterator it;
	
	// Check if sealed
	if (node->isSealed())
		return;
	
	// Finalize nodes in correct order
	node->finalize();
	for (it=node->begin(); it!=node->end(); ++it)
		finalize(*it);
	node->finalizeAfter();
}


/**
 * Opens a scene from a file.
 * 
 * @param filename Path to the file.
 */
void Scene::open(string filename) {
	
	Node *current=root, *node;
	Parser parser;
	vector<Tag> tags;
	vector<Tag>::iterator it;
	
	// Parse file
	this->filename = filename;
	filename = FileUtility::replaceEnvironmentVariable(filename);
	parser.open(filename);
	
	// Look through tags
	tags = parser.getTags();
	for (it=tags.begin(); it!=tags.end(); ++it) {
		
		// Step back on closing tags
		if (it->isClosing()) {
			current = current->getParent();
			continue;
		}
		
		// Create node and update current
		node = Factory::create(*it, filename);
		current->addChild(node);
		if (!it->isLeaf())
			current = node;
	}
}


/**
 * Allows nodes in graph to associate and finalize themselves.
 */
void Scene::prepare() {
	
	associate(root);
	finalize(root);
}


/**
 * Prints all the nodes in the scene.
 */
void Scene::print() {
	
	typedef pair<Node*,int> NodeLevel;
	int level;
	Node *node;
	stack<NodeLevel> s;
	vector<Node*>::const_reverse_iterator it;
	vector<Node*> children;
	string indent;
	
	// Print
	s.push(NodeLevel(root,0));
	while (!s.empty()) {
		node = s.top().first;
		level = s.top().second;
		s.pop();
		cout << Text::indent(level) << *node << endl;
		if (node->areChildrenPrintable()) {
			children = node->getChildren();
			for (it=children.rbegin(); it!=children.rend(); ++it) {
				s.push(NodeLevel(*it, level+1));
			}
		}
	}
}


/**
 * Replaces the root of the scene with a new node.
 */
void Scene::setRoot(Node *node) {
	
	// Test for bad input
	if (root->hasChildren()) {
		throw "[Scene] Cannot set root when it already has children.";
	} else if (node == NULL) {
		throw "[Scene] Cannot set root to NULL.";
	}
	
	// Make node new root
	delete root;
	root = node;
}


