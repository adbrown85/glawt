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
	
	Uniform *uniform;
	int location;
	map<Uniform*,int>::iterator ui;
	
	// Print what we found
	for (ui=locations.begin(); ui!=locations.end(); ++ui) {
		uniform = ui->first;
		location = ui->second;
		uniform->setLocation(location);
	}
}


void Instance::associate() {
	
	Node::iterator it;
	
	// Find group
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
}


void Instance::finalizeAfter() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Uniform *uniform;
	
	// Search all children for uniforms
	q.push(this);
	while (!q.empty()) {
		node = q.front();
		if ((uniform = dynamic_cast<Uniform*>(node)))
			locations[uniform] = uniform->getLocation();
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

