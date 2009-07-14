/*
 * Shape.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Drawable.hpp"
#include "Node.hpp"
#include "Selectable.hpp"
#include "Translation.hpp"
#include "Vector.hpp"
using std::set;
using std::string;
using std::ostream;
using std::ostringstream;



/**
 * @brief
 *     Base class for a 3D object in the scene.
 * @ingroup graph
 */
class Shape : public Drawable,
              public Node,
              public Selectable {
	
	
	public :
		
		Shape();
		
		virtual string attributes() const;
		friend ostream& operator<<(ostream &stream,
		                           const Shape &item);
		void setStyle(GLenum style) {this->style = style;}
		
		Translation *translation; 
	
	
	protected : 
		
		GLenum style;
};


#endif
