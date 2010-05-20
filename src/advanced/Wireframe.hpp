/*
 * Wireframe.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Node.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Causes only the edges of shapes to be drawn.
 */
class Wireframe : public Applicable {
public:
	Wireframe(const Tag &tag);
	virtual void apply();
	virtual void remove();
	virtual string toString() const;
private:
	GLenum mode;
	string faces;
};


#endif
