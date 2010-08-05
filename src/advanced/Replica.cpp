/*
 * Replica.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Replica.hpp"


Replica::Replica(const Tag &tag) : Clone(tag) {
	
}


void Replica::apply() {
	
	Clone::apply();
	
	applyReplacements();
}


void Replica::applyReplacements() {
	
	map<Placeholder*,Replacement*>::iterator it;
	
	for (it=placeholders.begin(); it!=placeholders.end(); ++it) {
		(it->first)->mimic((it->second));
	}
}


void Replica::associate() {
	
	Clone::associate();
	
	// Find
	findReplacements();
	findPlaceholders();
	
	// Apply
	applyReplacements();
}


void Replica::associateAfter() {
	
	Clone::associateAfter();
	
	removeReplacements();
}


void Replica::finalize() {
	
	Clone::finalize();
	
	applyReplacements();
}


void Replica::finalizeAfter() {
	
	Clone::finalizeAfter();
	
	removeReplacements();
}


/** Look for Replacement nodes. */
void Replica::findReplacements() {
	
	Node::iterator it;
	Node *node;
	Replacement *replacement;
	
	// Check each child
	for (it=begin(); it!=end(); ++it) {
		node = (*it);
		replacement = dynamic_cast<Replacement*>(node);
		if (replacement != NULL) {
			replacements[replacement->getOf()] = replacement;
		}
	}
}


/** Look for Placeholder nodes. */
void Replica::findPlaceholders() {
	
	Node *node;
	Node::iterator ni;
	queue<Node*> Q;
	Placeholder *placeholder;
	map<string,Replacement*>::iterator ri;
	
	Q.push(getLink());
	while (!Q.empty()) {
		node = Q.front();
		placeholder = dynamic_cast<Placeholder*>(node);
		if (placeholder != NULL) {
			ri = replacements.find(placeholder->getName());
			if (ri != replacements.end()) {
				placeholders[placeholder] = ri->second;
			}
		}
		for (ni=node->begin(); ni!=node->end(); ++ni) {
			Q.push((*ni));
		}
		Q.pop();
	}
}


/** Reset all the placeholders. */
void Replica::remove() {
	
	Clone::remove();
	
	removeReplacements();
}


/** Reset all the placeholders. */
void Replica::removeReplacements() {
	
	map<Placeholder*,Replacement*>::iterator it;
	
	for (it=placeholders.begin(); it!=placeholders.end(); ++it) {
		(it->first)->clear();
	}
}


/** @return String made from the node's attributes. */
string Replica::toString() const {
	
	ostringstream stream;
	
	stream << Clone::toString();
	stream << " replacements='" << replacements.size() << "'"
	       << " placeholders='" << placeholders.size() << "'";
	return stream.str();
}

