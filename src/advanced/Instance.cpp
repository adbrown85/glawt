/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


/** Initializes the @e of and @e suppress attributes. */
Instance::Instance(const Tag &tag) : Node(tag) {
	
	ostringstream stream;
	
	// Name of group
	tag.get("of", of);
	
	// Suppress errors
	if (!tag.get("suppress", suppress, false)) {
		suppress = true;
	}
	suppressor.setEnabled(suppress);
	
	// Nodes to exclude
	tag.get("exclude", exclude, false);
	
	// Duplicate
	stream << "duplicate of='" << of << "'";
	children.insert(begin(), Factory::create(stream.str()));
}


/** Resets all the shapes and uniforms to be under this instance. */
void Instance::apply() {
	
	// Restore
	restoreShapes();
	restoreUniforms();
	restoreExclusions();
}


/** Finds all shapes and uniforms and saves their state for this instance. */
void Instance::associateAfter() {
	
	// Find
	findShapes();
	findUniforms();
	findExclusions();
	
	// Save
	saveShapes();
	saveUniforms();
}


/** Resets all the shapes and uniforms to be under this instance. */
void Instance::finalize() {
	
	// Restore
	restoreShapes();
	restoreUniforms();
	
	// Suppression
	suppressor.start();
}


/** Stores the locations of the uniforms so they can be reset later. */
void Instance::finalizeAfter() {
	
	// Save
	saveShapes();
	saveUniforms();
	
	// Suppression
	if (suppressor.check() > 0) {
		suppressor.print(getTag());
	}
}


/** Looks for excluded shapes. */
void Instance::findExclusions() {
	
	Shape *shape;
	map<Shape*,ShapeSnapshot>::iterator si;
	map<string,Shape*>::iterator ei;
	istringstream stream;
	string name;
	
	// Build list of excluded names
	stream.str(exclude);
	stream >> name;
	while (stream) {
		exclusions[name] = NULL;
		stream >> name;
	}
	
	// Find the shapes
	for (si=shapes.begin(); si!=shapes.end(); ++si) {
		shape = si->first;
		name = shape->getName();
		ei = exclusions.find(name);
		if (ei != exclusions.end()) {
			exclusions[name] = shape;
		}
	}
}


/** Finds all the shapes in the group. */
void Instance::findShapes() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree for uniforms
	q.push(this);
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
void Instance::findUniforms() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Uniform *uniform;
	
	// Search subtree for uniforms
	q.push(this);
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
void Instance::restoreShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setAttributes((it->second).attributes);
	}
}


/** Resets the uniforms to their stored snapshots. */
void Instance::restoreUniforms() {
	
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setLocation((it->second).location);
	}
}


/** Resets shapes set to be excluded. */
void Instance::restoreExclusions() {
	
	map<string,Shape*>::iterator it;
	Shape* shape;
	
	// Reset exclusions
	for (it=exclusions.begin(); it!=exclusions.end(); ++it) {
		shape = it->second;
		if (shape != NULL) {
			shape->setExcluded(true);
		}
	}
}


/** Reverses setting shapes to be excluded. */
void Instance::remove() {
	
	map<string,Shape*>::iterator it;
	Shape* shape;
	
	// Reverse exclusions
	for (it=exclusions.begin(); it!=exclusions.end(); ++it) {
		shape = it->second;
		if (shape != NULL) {
			shape->setExcluded(false);
		}
	}
}


/** Saves snapshots of the shapes. */
void Instance::saveShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		(it->second).attributes = (it->first)->getAttributes();
	}
}


/** Saves snapshots of the uniforms. */
void Instance::saveUniforms() {
	
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		(it->second).location = (it->first)->getLocation();
	}
}


/** @return Adds @e of and @e suppress attributes to description. */
string Instance::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'"
	       << " suppress='" << (suppress?'T':'F') << "'"
	       << " exclude='" << exclude << "'";
	return stream.str();
}

