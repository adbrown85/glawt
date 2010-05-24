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
#include "Exception.hpp"
#include "Identifiable.hpp"        // Picking IDs
#include "Manipulator.hpp"         // Pass to Painter, check if picked
#include "Node.hpp"                // Checking depth
#include "Painter.hpp"             // Paints items into pick buffers
#include "Scene.hpp"               // Pass root node to Painter
#define PICK_BUFFER_SIZE 32
using namespace std;


/**
 * @ingroup frontend
 * @brief Determines which item is under the mouse cursor.
 */
class Picker {
public:
	Picker(Scene *scene, Canvas *canvas);
	void addManipulators(vector<Manipulator*> manipulators);
	pair<GLuint,GLuint> pick(int x, int y);
protected:
	pair<GLuint,GLuint> chooseItem();
	void finish();
	void initialize(int x, int y);
	void storeIDsOfItems();
private:
	GLuint buf[PICK_BUFFER_SIZE];
	map<GLuint,GLuint> ids;
	Painter *painter;
	Scene *scene;
};


#endif
