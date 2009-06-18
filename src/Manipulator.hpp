/*
 * Item.hpp
 *     Generic item class.  Also defines ItemSet.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __MANIPULATOR_HEADER__
#define __MANIPULATOR_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Identifiable.hpp"
#include "Item.hpp"
#include "Vector.hpp"
using std::string;



class Manipulator : public Identifiable  {
	
	
	public :
		
		Manipulator() {
			className = "Manipulator";
			id = ++count;
			size = 1.0;
		}
		
		void copy(const Item &item);
		virtual void draw() const = 0;
		
		int getID() const {return id;}
		void setPosition(float x, float y, float z) {position.set(x, y, z);}
	
	
	protected : 
		
		float size;
		int id;
		string className;
		Vector position, rotation;
		
		static int count;
};


#endif
