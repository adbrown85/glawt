/*
 * Shape.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <string>
#include "Node.hpp"
#include "Selectable.hpp"
#include "Translation.hpp"
using std::string;
using std::ostream;



/**
 * @ingroup graph
 * @brief
 *     Base class for a 3D object in the scene.
 */
class Shape : public Node,
              public Selectable {
	
	
	public :
		
		Translation *translation;
		
		Shape();
		GLenum getStyle() {return style;}
		void setStyle(GLenum style) {this->style = style;}
		
		friend ostream& operator<<(ostream &stream,
		                           const Shape &item);
	
	
	protected : 
		
		GLenum style;
};


#endif
