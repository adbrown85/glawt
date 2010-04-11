/*
 * Picker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PICKER_HPP
#define PICKER_HPP
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Identifiable.hpp"        // Picking IDs
#include "Manipulator.hpp"         // Pass to Painter, check if picked
#include "Node.hpp"                // Checking depth
#include "Painter.hpp"             // Paints items into pick buffers
#include "Scene.hpp"               // Pass root node to Painter
#define PICK_BUFFER_SIZE 32
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Determines which item is under the mouse cursor.
 */
class Picker {
	
	public :
		
		static pair<GLuint,GLuint> pick(Scene *scene,
		                           vector<Manipulator*> &manipulators,
		                           int x,
		                           int y);
	
	private:
		
		static GLuint buf[PICK_BUFFER_SIZE];
		static map<GLuint,GLuint> ids;
		
		static pair<GLuint,GLuint> chooseItem(Scene *scene);
		static void finish();
		static void initialize(int x, int y);
		static void storeIDsOfItems();
};


#endif
