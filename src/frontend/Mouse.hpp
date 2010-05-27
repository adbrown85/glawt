/*
 * Mouse.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseClickHelper.hpp"
#include "MouseDragHelper.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief %Mouse control for the %Display.
 * 
 * @todo Need to deallocate manipulators.
 */
class Mouse : public Control, public CommandListener {
public:
	Mouse(Delegate *delegate);
	virtual void install();
	static void onClick(int button, int action, int x, int y);
	static void onDrag(int x, int y);
	virtual void onCommandEvent(int command);
protected:
	void initBindings();
	void initData();
	void initManipulators();
	void enableScaleManipulators();
	void enableTranslateManipulators();
private:
	MouseData data;
	MouseClickHelper clickHelper;
	MouseDragHelper dragHelper;
	static Mouse *obj;
};


#endif
