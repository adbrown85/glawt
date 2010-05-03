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
	
	vector<Node*>::iterator it;
	vector<Node*> children;
	
	// Find group
	group = Group::find(this, of);
	if (group == NULL) {
		ostringstream msg;
		msg << "[Instance] Could not find group with name '" << of << "'";
		throw msg.str().c_str();
	}
	
	// Get children
	children = group->getChildren();
	for (it=children.begin(); it!=children.end(); ++it) {
		addChild(*it);
	}
}


void Instance::finalizeAfter() {
	
	Node *node;
	queue<Node*> q;
	Uniform *uniform;
	vector<Node*>::iterator it;
	vector<Node*> children;
	
	// Search all children for uniforms
	q.push(this);
	while (!q.empty()) {
		node = q.front();
		if ((uniform = dynamic_cast<Uniform*>(node)))
			locations[uniform] = uniform->getLocation();
		children = node->getChildren();
		for (it=children.begin(); it!=children.end(); ++it)
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

