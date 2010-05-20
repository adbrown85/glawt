/*
 * NodeEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeEvent.hpp"


void NodeNotifier::addListener(NodeListener *listener, int type) {
	
	list<NodeListener*> *subset;
	
	// Get listeners of correct type
	subset = getListenersFor(type);
	if (subset == NULL) {
		listeners[type] = list<NodeListener*>();
		subset = getListenersFor(type);
	}
	
	// Add the listener
	subset->push_back(listener);
}


list<NodeListener*>* NodeNotifier::getListenersFor(int type) {
	
	map<int, list<NodeListener*> >::iterator it;
	
	it = listeners.find(type);
	if (it != listeners.end())
		return &(it->second);
	else
		return NULL;
}


void NodeNotifier::fireEvent(NodeEvent event) {
	
	list<NodeListener*> *subset;
	list<NodeListener*>::iterator it;
	
	// Send to each listener of this type
	subset = getListenersFor(event.getType());
	if (subset == NULL)
		return;
	
	for (it=subset->begin(); it!=subset->end(); ++it) {
		(*it)->onNodeEvent(event);
	}
}

