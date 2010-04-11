/*
 * Manipulator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Delegate.hpp"
#include "Drawable.hpp"
#include "Identifiable.hpp"
#include "Scene.hpp"
#include "Vector.hpp"


/**
 * @ingroup frontend
 * @brief
 *     Abstract base class for an item that manipulates other items.
 */
class Manipulator : public Drawable  {
	
	public :
		
		Manipulator() {this->delegate = NULL;}
		
		virtual void use(Scene *scene,
		                 const Vector &movement,
		                 GLuint shapeID) = 0;
		Vector getAxis() {return axis;}
		void setDelegate(Delegate *delegate) {this->delegate = delegate;}
	
	protected :
		
		Delegate *delegate;
		Vector axis;
};


#endif
