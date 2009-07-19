/*
 * Picker.hpp
 *     Picks items in a scene.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef PICKER_HPP
#define PICKER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <typeinfo>
#include <vector>
#include "Identifiable.hpp"        // Picking IDs
#include "Manipulator.hpp"         // Pass to Painter, check if picked
#include "Painter.hpp"             // Paints items into pick buffers
#include "Scene.hpp"               // Pass root node to Painter
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
		                   vector<Manipulator*> &manipulators,
		                   int x,
		                   int y);
	
	
	private:
		
		static GLuint buf[PICK_BUFFER_SIZE];
		static set<GLuint> ids;
		
		static GLuint chooseItem(Scene *scene);
		static void finish();
		static void initialize(int x, int y);
		static void storeIDsOfItems();
};


#endif
