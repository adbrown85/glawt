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
		
		Manipulator();
		Vector getAxis() const;
		void setDelegate(Delegate *delegate);
		virtual void use(Scene *scene,
		                 const Vector &movement,
		                 GLuint shapeID) = 0;
	
	protected :
		
		Delegate *delegate;
		Vector axis;
};


inline Manipulator::Manipulator() {
	this->delegate = NULL;
}

inline Vector Manipulator::getAxis() const {
	return axis;
}

inline void Manipulator::setDelegate(Delegate *delegate) {
	this->delegate = delegate;
}


#endif
