/*
 * NodeException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODEEXCEPTION_HPP
#define NODEEXCEPTION_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Exception.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief %Exception thrown from a node.
 * 
 * Automatically initializes the exception's message to the tag's location.
 */
class NodeException : public Exception {
public:
	NodeException(const Tag &tag);
};


#endif
