/*
 * Replica.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Replica.hpp"


/** Initialize attributes. */
Replica::Replica(const Tag &tag) : Clone(tag) {
	
}


/** Substitute placeholders with replacements. */
void Replica::apply() {
	
	Clone::apply();
	
	applyReplacements();
}


/** Substitute placeholders with replacements. */
void Replica::applyReplacements() {
	
	map<Placeholder*,Replacement*>::iterator it;
	
	for (it=replacements.begin(); it!=replacements.end(); ++it) {
		(it->first)->mimic((it->second));
	}
}


/** Find and apply replacements before children associate. */
void Replica::associate() {
	
	Clone::associate();
	
	findReplacements();
	applyReplacements();
}


/** Remove replacements after children associate. */
void Replica::associateAfter() {
	
	Clone::associateAfter();
	
	removeReplacements();
}


/** Apply replacements before children have been finalized. */
void Replica::finalize() {
	
	Clone::finalize();
	
	applyReplacements();
}


/** Remove replacements after children have been finalized. */
void Replica::finalizeAfter() {
	
	Clone::finalizeAfter();
	
	removeReplacements();
}


/** Look for replacements. */
void Replica::findReplacements() {
	
	Node *node;
	Node::iterator ni;
	map<string,Replacement*> catalog;
	map<string,Replacement*>::iterator ri;
	Placeholder *placeholder;
	queue<Node*> Q;
	Replacement *replacement;
	
	// Index replacement nodes by name
	for (ni=begin(); ni!=end(); ++ni) {
		node = (*ni);
		replacement = dynamic_cast<Replacement*>(node);
		if (replacement != NULL) {
			catalog[replacement->getOf()] = replacement;
		}
	}
	
	// Search for placeholders and store with replacement
	Q.push(getLink());
	while (!Q.empty()) {
		node = Q.front();
		placeholder = dynamic_cast<Placeholder*>(node);
		if (placeholder != NULL) {
			ri = catalog.find(placeholder->getName());
			if (ri != catalog.end()) {
				replacements[placeholder] = ri->second;
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
	
	for (it=replacements.begin(); it!=replacements.end(); ++it) {
		(it->first)->clear();
	}
}


/** @return String made from the node's attributes. */
string Replica::toString() const {
	
	ostringstream stream;
	
	stream << Clone::toString();
	stream << " replacements='" << replacements.size() << "'";
	return stream.str();
}

