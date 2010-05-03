/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


Instance::Instance(const Tag &tag) {
	
	tag.get("of", of);
}


void Instance::apply() {
	
	int location;
	map<Uniform*,Program*>::iterator pi;
	map<Uniform*,int>::iterator li;
	Program *program;
	Uniform *uniform;
	
	// Set programs
	for (pi=programs.begin(); pi!=programs.end(); ++pi) {
		uniform = pi->first;
		program = pi->second;
		cout << "Setting " << uniform << " to " << program << endl;
		uniform->setProgram(program);
	}
	
	// Set locations
	for (li=locations.begin(); li!=locations.end(); ++li) {
		uniform = li->first;
		location = li->second;
		cout << "Setting " << uniform << " to " << location << endl;
		uniform->setLocation(location);
	}
}


void Instance::associate() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Uniform *uniform;
	
	// Find the group
	group = Group::find(this, of);
	if (group == NULL) {
		ostringstream msg;
		msg << "[Instance] Could not find group with name '" << of << "'";
		throw msg.str().c_str();
	}
	
	// Get children from group
	for (it=group->begin(); it!=group->end(); ++it) {
		addChild(*it);
	}
	
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


void Instance::associateAfter() {
	
	list<Uniform*>::iterator ui;
	
	// Get programs from the uniforms
	for (ui=uniforms.begin(); ui!=uniforms.end(); ++ui) {
		programs[(*ui)] = (*ui)->getProgram();
	}
}


void Instance::finalize() {
	
	map<Uniform*,Program*>::iterator pi;
	Node::iterator ni;
	Program *program;
	Uniform *uniform;
	
	// Make sure children's parents point to this instance
	for (ni=begin(); ni!=end(); ++ni) {
		(*ni)->setParent(this);
	}
	
	// Set programs in uniforms
	for (pi=programs.begin(); pi!=programs.end(); ++pi) {
		uniform = pi->first;
		program = pi->second;
		uniform->setProgram(program);
	}
}


void Instance::finalizeAfter() {
	
	list<Uniform*>::iterator ui;
	
	// Get locations from uniforms
	for (ui=uniforms.begin(); ui!=uniforms.end(); ++ui) {
		locations[(*ui)] = (*ui)->getLocation();
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

