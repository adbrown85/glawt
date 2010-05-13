/*
 * Attachable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ATTACHABLE_HPP
#define ATTACHABLE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/gl.h>
using namespace std;


/**
 * @interface Attachable
 * @ingroup graph
 * @brief Node that can be attached to another node.
 */
class Attachable {
public:
	virtual void attach() = 0;
	virtual void setIndex(GLint index) = 0;
	virtual void setLocation(GLuint location) = 0;
};


#endif
