/*
 * Fullscreen.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FULLSCREEN_HPP
#define FULLSCREEN_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Drawable.hpp"
#include "Node.hpp"
#include "Tag.hpp"


/**
 * @ingroup advanced
 * @brief Polygon that takes up the entire window.
 */
class Fullscreen : public Drawable {
public:
	Fullscreen(const Tag &tag);
	virtual void draw() const;
protected:
	virtual void initCoordinates();
	virtual void initIndices();
	virtual void initPoints();
private:
	static bool loaded;
	static GLfloat coordinates[4][3];
	static GLfloat points[4][3];
	static GLubyte indices[4];
};


#endif

