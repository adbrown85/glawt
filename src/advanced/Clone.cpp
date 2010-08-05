/*
 * Clone.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Clone.hpp"


/** Initializes attributes. */
Clone::Clone(const Tag &tag) : Instance(tag) {
	
	// Suppress errors
	if (!tag.get("suppress", suppress, false)) {
		suppress = true;
	}
	suppressor.setEnabled(suppress);
}


/** Resets all the shapes and uniforms to be under this instance. */
void Clone::apply() {
	
	// Restore
	restoreShapes();
	restoreUniforms();
}


/** Finds all shapes and uniforms. */
void Clone::associate() {
	
	Instance::associate();
	
	// Find
	findShapes();
	findUniforms();
}


/**  Saves the states of the shapes and uniforms. */
void Clone::associateAfter() {
	
	// Save
	saveShapes();
	saveUniforms();
}


/** Resets all the shapes and uniforms to be under this instance. */
void Clone::finalize() {
	
	Instance::finalize();
	
	// Restore
	restoreShapes();
	restoreUniforms();
	
	// Suppression
	suppressor.start();
}


/** Stores the locations of the uniforms so they can be reset later. */
void Clone::finalizeAfter() {
	
	// Save
	saveShapes();
	saveUniforms();
	
	// Suppression
	if (suppressor.check() > 0) {
		suppressor.print(getTag());
	}
}


/** Finds all the shapes in the group. */
void Clone::findShapes() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree for uniforms
	q.push(getLink());
	while (!q.empty()) {
		node = q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL)
			shapes[shape] = ShapeSnapshot();
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


/** Finds all the uniforms in the group. */
void Clone::findUniforms() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Uniform *uniform;
	
	// Search subtree for uniforms
	q.push(getLink());
	while (!q.empty()) {
		node = q.front();
		uniform = dynamic_cast<Uniform*>(node);
		if (uniform != NULL) {
			uniforms[uniform] = UniformSnapshot();
			suppressor.add(uniform);
		}
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


/** Resets the shapes to their stored snapshots. */
void Clone::restoreShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setAttributes((it->second).attributes);
	}
}


/** Resets the uniforms to their stored snapshots. */
void Clone::restoreUniforms() {
	
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setLocation((it->second).location);
	}
}


/** Saves snapshots of the shapes. */
void Clone::saveShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		(it->second).attributes = (it->first)->getAttributes();
	}
}


/** Saves snapshots of the uniforms. */
void Clone::saveUniforms() {
	
	GLint location;
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		location = (it->first)->getLocation();
		(it->second).location = location;
	}
}


/** @return Adds @e suppress attribute to description. */
string Clone::toString() const {
	
	ostringstream stream;
	
	stream << Instance::toString();
	stream << " suppress='" << (suppress?'T':'F') << "'"
	       << " shapes='" << shapes.size() << "'"
	       << " uniforms='" << uniforms.size() << "'";
	return stream.str();
}

