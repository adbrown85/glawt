/*
 * Scene.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Scene.hpp"



/**
 * Creates and initializes a new scene.
 */
Scene::Scene() {
	
	// Initialize
	this->width = 640;
	this->height = 480;
	reset();
}



/**
 * Creates and initializes a new scene.
 * 
 * @param width
 *     Width of the window for the scene.
 * @param height
 *     Height of the window for the scene.
 */
Scene::Scene(int width,
             int height) {
	
	// Initialize
	this->width = width;
	this->height = height;
	reset();
}



/**
 * Adds the node as a child of the scene's root.
 */
void Scene::add(Node *node) {
	
	rootNode.addChild(node);
}



/**
 * Returns the scene's rotation as a matrix.
 */
Matrix Scene::getRotationMatrix() const {
	
	// Return matrix
	return rotation.getMatrix();
}



/**
 * Allows nodes in graph to associate and finalize themselves.
 */
void Scene::prepare() {
	
	rootNode.associateTree();
	rootNode.finalizeTree();
}



/**
 * Prints the list of items stored.
 */
void Scene::print() {
	
	rootNode.printTree();
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
void Scene::rotate(float angle, float x, float y, float z) {
	
	Quaternion rotation;
	
	// Combine quaternion with current rotation
	rotation.set(angle, x, y, z);
	this->rotation = rotation * this->rotation;
}



/**
 * Sets the rotation of the scene using axis/angle.
 */
void Scene::setRotation(float angle, float x, float y, float z) {
	
	// Set rotation
	rotation.set(angle, x, y, z);
}
