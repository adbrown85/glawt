/*
 * Shadow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shadow.hpp"


/** Initializes attributes. */
Shadow::Shadow(const Tag &tag) : Node(tag) {
	
	// Retrieve from tag
	tag.get("of", of, true, false);
	tag.get("from", from, true, false);
}


/** Finds the group and light. */
void Shadow::associate() {
	
	findGroup();
	findLight();
	findTransforms();
}


/** Finds the group named by @e of. 
 * 
 * @throws NodeException if group not found.
 */
void Shadow::findGroup() {
	
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Shadow] Could not find group named '" << of << "'.";
		throw e;
	}
}


/** Finds the light named by @e from.
 * 
 * @throws NodeException if light not found.
 */
void Shadow::findLight() {
	
	Node *node;
	
	// Find the node
	node = Nameable::search(Node::findRoot(this), from);
	if (node == NULL) {
		NodeException e(tag);
		e << "[Shadow] Light named '" << from << "' not found.";
		throw e;
	}
	
	// Make sure it's a light
	light = dynamic_cast<Light*>(node);
	if (light == NULL) {
		NodeException e(tag);
		e << "[Shadow] Node named '" << from << "' is not a light.";
		throw e;
	}
}


/** Finds the transforms above the light and group and adds listeners. */
void Shadow::findTransforms() {
	
	list<Transformation*> transforms;
	list<Transformation*>::iterator it;
	
	// Get all the transforms
	Transformation::search(group, transforms);
	Transformation::findAll(light, transforms);
	
	// Add listeners
	for (it=transforms.begin(); it!=transforms.end(); ++it) {
		(*it)->addListener(this, NodeEvent::MODIFY);
	}
}


/** Renders the scene from the light's point of view into the shadow map. */
void Shadow::onNodeEvent(NodeEvent &event) {
	
}


/** @return String comprised of the node's attributes. */
string Shadow::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'"
	       << " from='" << from << "'";
	return stream.str();
}

