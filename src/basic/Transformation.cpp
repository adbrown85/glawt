/*
 * Transformation.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transformation.hpp"


/** Adds a listener to this node. */
void Transformation::addListener(NodeListener *listener) {
	
	listeners.push_back(listener);
}


/** Sends a notification to each of the listeners. */
void Transformation::fireUpdate() {
	
	list<NodeListener*>::iterator it;
	
	for (it=listeners.begin(); it!=listeners.end(); ++it) {
		(*it)->nodeUpdated();
	}
}

