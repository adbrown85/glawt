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


void Replica::associate() {
	
	Clone::associate();
	
	findExclusions();
	
	// Make replacements
	//   - Search for replacements in children and store them
	//   - Search group for placeholders
	//   - For each placeholder,
	//       - Check if I have a replacement for it
	//       - If so, make a node with replacement's children and store it
	//       - On apply, set that node as the placeholder's child
	//       - On remove, clear the placeholder's child
	
	// Will need a list of replacements
	// Will need a map of placeholders map<Placeholder*,Node*>
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


void Replica::remove() {
	
	removeExclusions();
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


/** @return Adds @e exclude attribute to description. */
string Replica::toString() const {
	
	ostringstream stream;
	
	stream << Clone::toString();
	stream << " exclude='" << exclude << "'";
	return stream.str();
}

