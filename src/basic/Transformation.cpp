/*
 * Transformation.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transformation.hpp"


/** Adds a modify listener to this node. */
void Transformation::addListener(NodeListener *listener) {
	
	notifier.addListener(listener, NodeEvent::MODIFY);
}


/** Fires a modify event. */
void Transformation::fireEvent() {
	
	notifier.fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}

