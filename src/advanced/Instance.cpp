/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


Instance::Instance(const Tag &tag) : Applicable(tag) {
	
	tag.get("of", of);
}


void Instance::apply() {
	
	assignPrograms();
	assignLocations();
}


void Instance::assignLocations() {
	
	int location;
	map<Uniform*,int>::iterator it;
	Uniform *uniform;
	
	// Set each uniform to its location
	for (it=locations.begin(); it!=locations.end(); ++it) {
		uniform = it->first;
		location = it->second;
		uniform->setLocation(location);
	}
}


void Instance::assignParents() {
	
	Node::iterator ni;
	
	// Make sure children's parents point to this instance
	for (ni=begin(); ni!=end(); ++ni) {
		(*ni)->setParent(this);
	}
}


void Instance::assignPrograms() {
	
	map<Uniform*,Program*>::iterator it;
	Program *program;
	Uniform *uniform;
	
	// Set programs
	for (it=programs.begin(); it!=programs.end(); ++it) {
		uniform = it->first;
		program = it->second;
		uniform->setProgram(program);
	}
}


void Instance::associate() {
	
	findGroup();
	findChildren();
	findUniforms();
}


void Instance::associateAfter() {
	
	findPrograms();
}


void Instance::finalize() {
	
	// Reset uniforms for this instance
	assignParents();
	assignPrograms();
}


void Instance::finalizeAfter() {
	
	findLocations();
}


void Instance::findChildren() {
	
	Node::iterator it;
	
	// Get children from group
	for (it=group->begin(); it!=group->end(); ++it) {
		addChild(*it);
	}
}


/**
 * @throws NodeException if the group cannot be found
 */
void Instance::findGroup() {
	
	// Find the group
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Instance] Could not find group with name '" << of << "'";
		throw e;
	}
}


void Instance::findLocations() {
	
	list<Uniform*>::iterator it;
	
	// Get locations from uniforms
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		locations[(*it)] = (*it)->getLocation();
	}
}


void Instance::findPrograms() {
	
	list<Uniform*>::iterator ui;
	
	// Get programs from the uniforms
	for (ui=uniforms.begin(); ui!=uniforms.end(); ++ui) {
		programs[(*ui)] = (*ui)->getProgram();
	}
}


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
		if (uniform != NULL)
			uniforms.push_back(uniform);
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


void Instance::remove() {
	
}


string Instance::toString() const {
	
	ostringstream stream;
	
	stream << Applicable::toString();
	stream << " of='" << of << "'";
	return stream.str();
}

