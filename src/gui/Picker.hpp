/*
 * Picker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PICKER_HPP
#define PICKER_HPP
#include "common.h"
#include <cfloat>
#include <climits>
#include <typeinfo>
#include "Manipulator.hpp"         // Pass to Painter, check if picked
#include "Node.hpp"                // Checking depth
#include "Painter.hpp"             // Paints items into pick buffers
#define PICK_BUFFER_SIZE 32
using namespace std;


/** @brief Determines which item is under the mouse cursor.
 * @ingroup gui
 */
class Picker {
public:
	Picker(Scene *scene, Canvas *canvas);
	void addManipulators(list<Manipulator*> manipulators);
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
	Canvas *canvas;
	Scene *scene;
};


#endif
