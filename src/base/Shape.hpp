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
#include "Node.hpp"
#include "Selectable.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup base
 * @brief
 *     Base class for a 3D object in the scene.
 */
class Shape : public Node,
              public Selectable {
	
	public :
		
		Shape(float size=1.0);
		Shape(const Tag &tag);
		virtual string toString() const;
		
		GLenum getStyle() const;
		void setStyle(GLenum style);
	
	protected : 
		
		GLenum style;
		
		virtual void computeDepth(Matrix &matrx);
};


inline GLenum Shape::getStyle() const {return style;}
inline void Shape::setStyle(GLenum style) {this->style = style;}

#endif

