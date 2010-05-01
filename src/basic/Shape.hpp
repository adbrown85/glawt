/*
 * Shape.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "Program.hpp"
#include "Selectable.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief
 *     Base class for a 3D object in the scene.
 */
class Shape : public Selectable {
public:
	Shape(const Tag &tag);
	virtual void associate();
	virtual void finalize();
	virtual GLenum getStyle() const;
	virtual void setStyle(GLenum style);
	virtual string toString() const;
protected: 
	GLenum style;
	GLint coordsLoc, pointsLoc, normalsLoc;
	Program *program;
	virtual void computeDepth(Matrix &matrx);
};


inline GLenum Shape::getStyle() const {return style;}
inline void Shape::setStyle(GLenum style) {this->style = style;}

#endif

