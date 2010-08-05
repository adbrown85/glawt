/*
 * Replica.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Replica.hpp"


Replica::Replica(const Tag &tag) : Clone(tag) {
	
	// Nodes to exclude
	tag.get("exclude", exclude, false);
}


void Replica::apply() {
	
	Clone::apply();
	
	applyExclusions();
	applyReplacements();
}


/** Excludes certain shapes. */
void Replica::applyExclusions() {
	
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


void Replica::applyReplacements() {
	
	map<Placeholder*,Replacement*>::iterator it;
	
	for (it=placeholders.begin(); it!=placeholders.end(); ++it) {
		(it->first)->mimic((it->second));
	}
}


void Replica::associate() {
	
	Clone::associate();
	
	findExclusions();
	findReplacements();
	findPlaceholders();
	
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


/** Looks for excluded shapes. */
void Replica::findExclusions() {
	
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


void Replica::remove() {
	
	removeExclusions();
	removeReplacements();
}


/** Removes exclusions from the shapes. */
void Replica::removeExclusions() {
	
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


void Replica::removeReplacements() {
	
	map<Placeholder*,Replacement*>::iterator it;
	
	for (it=placeholders.begin(); it!=placeholders.end(); ++it) {
		(it->first)->clear();
	}
}


/** @return Adds @e exclude attribute to description. */
string Replica::toString() const {
	
	ostringstream stream;
	
	stream << Clone::toString();
	if (!exclude.empty())
		stream << " exclude='" << exclude << "'";
	stream << " replacements='" << replacements.size() << "'"
	       << " placeholders='" << placeholders.size() << "'";
	return stream.str();
}

