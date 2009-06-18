/*
 * Translator.hpp
 *     Visual tool for moving items.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __TRANSLATOR_HEADER__
#define __TRANSLATOR_HEADER__
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Manipulator.hpp"



class Translator : public Manipulator {
	
	
	public :
		
		Translator() {
			cyl = gluNewQuadric();
			gluQuadricDrawStyle(cyl, GLU_FILL);
			className = "Translator";
		}
		
		virtual void draw() const;
	
	
	private:
		
		GLUquadric *cyl;
};


#endif
