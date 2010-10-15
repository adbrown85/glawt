/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


/** Initialize attributes. */
Instance::Instance(const Tag &tag) : Node(tag) {
	
	Tag linkTag;
	
	// Name of group
	tag.get("of", of, true, true);
	if (!tag.get("selectable", selectable, false)) {
		selectable = false;
	}
	
	// Exclusions
	tag.get("only", only, false);
	
	// Create link
	linkTag.setName("link");
	linkTag.setFilename(tag.getFilename());
	linkTag.setLine(tag.getLine());
	linkTag["to"] = of;
	link = new Link(linkTag);
	addChild(link);
}


/** Excludes certain shapes. */
void Instance::apply() {
	
	list<Shape*>::iterator it;
	
	// Reset exclusions
	for (it=exclusions.begin(); it!=exclusions.end(); ++it) {
		(*it)->setExcluded(true);
	}
}


/** Establishes the link and finds exclusions. */
void Instance::associate() {
	
	link->establish();
	if (!only.empty()) {
		findExclusions();
	}
}


/** Relinks all the children of the link. */
void Instance::finalize() {
	
	link->relink();
}


/** Looks for excluded shapes. */
void Instance::findExclusions() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	Shape *shape;
	
	Q.push(getLink());
	while (!Q.empty()) {
		node = Q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL) {
			if (shape->getName() != only) {
				exclusions.push_back(shape);
			}
		}
		for (it=node->begin(); it!=node->end(); ++it) {
			Q.push((*it));
		}
		Q.pop();
	}
}


/** Removes exclusions from the shapes. */
void Instance::remove() {
	
	list<Shape*>::iterator it;
	
	// Reset exclusions
	for (it=exclusions.begin(); it!=exclusions.end(); ++it) {
		(*it)->setExcluded(false);
	}
}


/** @return String made from the node's attributes. */
string Instance::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'"
	       << " selectable='" << (selectable?'T':'F') << "'";
	if (!only.empty())
		stream << " only='" << only << "'";
	return stream.str();
}

