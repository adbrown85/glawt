/*
 * NodeNotifier.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODENOTIFIER_HPP
#define NODENOTIFIER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>                          // Storing listeners
#include <list>                         // Storing listeners
#include "Node.hpp"
#include "NodeEvent.hpp"
#include "NodeListener.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Utility for notifying listeners of node events.
 */
class NodeNotifier {
public:
	void addListener(NodeListener *listener, int type);
	void fireEvent(NodeEvent event);
protected:
	list<NodeListener*>* getListenersFor(int type);
private:
	map<int, list<NodeListener*> > listeners;
};


#endif
