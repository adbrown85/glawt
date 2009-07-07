/*
 * Picker.hpp
 *     Picks items in a scene.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PICKER_HEADER__
#define __PICKER_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <typeinfo>
#include <vector>
#include "Item.hpp"
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Scene.hpp"
#include "Translator.hpp"
#define PICK_BUFFER_SIZE 32
using std::set;
using std::vector;



/**
 * @brief
 *     Determines which item is under the mouse cursor.
 * @ingroup frontend
 */
class Picker {
	
	
	public :
		
		static GLuint pick(Scene *scene,
		                   vector<Manipulator*> manipulators,
		                   int x,
		                   int y);
	
	
	private:
		
		static GLuint buf[PICK_BUFFER_SIZE];
		static set<GLuint> ids;
		
		static GLuint choose(Scene *scene);
		static void draw(Scene *scene,
		                 vector<Manipulator*> manipulators);
		static void finish();
		static void initialize(int x, int y);
		static void store();
};


#endif
