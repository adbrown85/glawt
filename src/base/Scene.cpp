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


Node* Scene::create(const Tag &tag) {
	
	map<string,Factory*>::iterator it;
	
	it = factories.find(tag.name );
	if (it != factories.end()) {
		return it->second->create(tag);
	} else {
		ostringstream msg;
		msg << "[Scene] Cannot find factory for '" << tag.name << "'.";
		throw msg.str().c_str();
	}
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


void Scene::install(Factory *factory) {
	
	set<string> tags;
	set<string>::iterator it;
	
	tags = factory->getTags();
	for (it=tags.begin(); it!=tags.end(); ++it) {
		factories[*it] = factory;
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
		parse();
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
}


void Scene::parse() {
	
	Node *current, *node;
	map<string,string>::const_iterator ai;
	string path;
	vector<Tag>::iterator ti;
	
	// Initialize
	current = &root;
	parser.open(filename);
	
	// Look through tags
	for (ti=parser.tags.begin(); ti!=parser.tags.end(); ++ti) {
		
		// Step back on closing tags
		if (ti->closing) {
			current = current->getParent();
			continue;
		}
		
		// Make "file" attributes relative to scene file
		ai = ti->attributes.find("file");
		if (ai != ti->attributes.end()) {
			path = FileUtility::getRelativePath(filename, ai->second);
			ti->attributes["file"] = path;
		}
		
		// Create node and update current
		node = create(*ti);
		current->addChild(node);
		if (!ti->empty)
			current = node;
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

