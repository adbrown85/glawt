/*
 * Manipulator.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __MANIPULATOR_HPP__
#define __MANIPULATOR_HPP__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Drawable.hpp"
#include "Identifiable.hpp"
#include "Scene.hpp"
#include "Vector.hpp"



/**
 * @brief
 *     Abstract base class for an item that manipulates other items.
 * @ingroup frontend
 */
class Manipulator : public Drawable, public Identifiable  {
	
	
	public :
		
		virtual void use(Scene *scene, const Vector &difference) = 0;
		
		Vector getAxis() {return axis;}
	
	
	protected :
		
		Vector axis;
};


#endif
