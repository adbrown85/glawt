/*
 * MouseDragHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSEDRAGHELPER_HPP
#define MOUSEDRAGHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <GL/glut.h>
#include "MouseHelper.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Handles mouse dragging actions for %Mouse.
 */
class MouseDragHelper : public MouseHelper {
public:
	MouseDragHelper(Interpreter *interpreter);
	void onDrag(int x, int y);
	void setBindings(multimap<int,Binding> bindings);
protected:
	void decideAxis();
	void tryBinding(Binding *binding);
	void tryBindings();
	bool useConstrained();
private:
	Vector axis, direction, movement;
	static char directions[2];
};


#endif
