/*
 * MouseHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSEHELPER_HPP
#define MOUSEHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Control.hpp"
#include "Vector.hpp"
using namespace std;


/* Shared data between all the mouse controls. */
struct MouseData {
	int button, modifier, state, x, y;
	float z;
	unsigned int itemID, iteration, shapeID;
	Manipulator *manipulator;
	Vector lastPosition;
};


/**
 * @ingroup frontend
 * @brief Generic helper control for a mouse action.
 */
class MouseHelper : public Control {
public:
	MouseHelper(Delegate *delegate);
	virtual int getModifier();
	virtual void install() {};
	virtual void setData(MouseData *data);
	virtual void updateCurrentData(int x, int y);
	virtual void updateLastData();
protected:
	MouseData *data;
};


#endif
