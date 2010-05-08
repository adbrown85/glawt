/*
 * NodeListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODELISTENER_HPP
#define NODELISTENER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;


/**
 * @ingroup graph
 * @interface NodeListener
 * @brief Object that is notified by a node.
 */
class NodeListener {
public:
	virtual void nodeUpdated() = 0;
};


#endif
