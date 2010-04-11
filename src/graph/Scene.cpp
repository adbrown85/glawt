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
 * @param width Width of the window for the scene.
 * @param height Height of the window for the scene.
 */
Scene::Scene(int width,
             int height) {
	
	// Initialize
	this->width = width;
	this->height = height;
	reset();
	last = &root;
}


/**
 * Adds a node as a child of the scene's last node.
 * 
 * @param node Node to add.
 */
void Scene::addToLast(Node *node) {
	
	last->addChild(node);
	last = node;
}


/**
 * Adds a node as a child of the scene's root.
 * 
 * @param node Node to add.
 */
void Scene::addToRoot(Node *node) {
	
	root.addChild(node);
	last = node;
}


/**
 * Changes the last node to its parent.
 */
void Scene::backup() {
	
	if (last == &root)
		return;
	last = last->getParent();
}


/**
 * Returns the scene's rotation as a matrix.
 */
Matrix Scene::getRotationMatrix() const {
	
	// Return matrix
	return rotation.getMatrix();
}


/**
 * Opens a scene from a file.
 * 
 * @param filename Path to the file.
 */
void Scene::open(string filename) {
	
	Factory factory(&root, filename);
	
	// Parse and process tags
	try {
		cerr << "[Scene] Opening '" << filename << "'..." << endl;
		factory.start();
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
	
	root.associateTree();
	root.finalizeTree();
}


/**
 * Prints the list of items stored.
 */
void Scene::print() {
	
	root.printTree();
}


/**
 * Resets the scene's camera information.
 */
void Scene::reset() {
	
	// Reset transformations
	position.set(0.0, 0.0, -10);
	rotation.set(0.0, 0.0, 0.0, 1.0);
}


/**
 * Rotates the scene by axis/angle.
 */
void Scene::rotate(float angle,
                   float x,
                   float y,
                   float z) {
	
	Quaternion rotation;
	
	// Combine quaternion with current rotation
	rotation.set(angle, x, y, z);
	this->rotation = rotation * this->rotation;
}


/**
 * Sets the rotation of the scene using axis/angle.
 */
void Scene::setRotation(float angle,
                        float x,
                        float y,
                        float z) {
	
	// Set rotation
	rotation.set(angle, x, y, z);
}


/**
 * Sorts the scene by depth using the rotation matrix.
 */
void Scene::sortByDepth() {
	
	Matrix rotMatrix;
	
	// Sort by depth using rotation matrix
	rotMatrix = getRotationMatrix();
	root.sortByDepth(rotMatrix);
}

