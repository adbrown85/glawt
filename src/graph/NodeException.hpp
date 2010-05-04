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


class NodeException : public Exception {
public:
	NodeException(const Tag &tag);
};


#endif
