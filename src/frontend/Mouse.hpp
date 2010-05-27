/*
 * Mouse.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Control.hpp"
#include "Picker.hpp"
using namespace std;


/** @brief %Mouse control for the %Display.
 * @ingroup frontend
 */
class Mouse : public Control,
              public CanvasListener, public CommandListener {
public:
	Mouse(Delegate *delegate);
	virtual void install();
	virtual void onCanvasEvent(const CanvasEvent &event);
	virtual void onCanvasEventButton(const CanvasEvent &event);
	virtual void onCanvasEventDrag(const CanvasEvent &event);
	virtual void onCommandEvent(int command);
protected:
	void addBindings();
	void addManipulators();
	void decideAxis();
	void enableScaleManipulators();
	void enableTranslateManipulators();
	float findDragAmount(int i);
	void pickItem();
private:
	Camera *camera;
	Binding *binding;
	CanvasState state, last;
	float depth;
	GLuint itemID, shapeID;
	Manipulator *manip;
	Vector axis, direction, movement;
	Picker picker;
	int iteration;
};


/** Installs the bindings for the mouse. */
inline void Mouse::addBindings() {
	
	Combo combo;
	
	// Mouse wheel up
	combo.trigger = CANVAS_WHEEL_UP;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_UP;
	add(Binding(combo, Command::ZOOM_IN, 1.0f));
	
	// Mouse wheel down
	combo.trigger = CANVAS_WHEEL_DOWN;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_UP;
	add(Binding(combo, Command::ZOOM_OUT, 1.0f));
	
	// Ctrl + Left button
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_CONTROL;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::GRAB, &itemID));
	
	// Left button drag in x
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'x';
	add(Binding(combo, Command::CIRCLE_Y, -1.0f));
	
	// Left button drag in y
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'y';
	add(Binding(combo, Command::CIRCLE_X, -1.0f));
	
	// Middle button drag in x
	combo.trigger = CANVAS_MIDDLE_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'x';
	add(Binding(combo, Command::TRACK, -1.0f));
	
	// Middle button drag in y
	combo.trigger = CANVAS_MIDDLE_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'y';
	add(Binding(combo, Command::BOOM, 1.0f));
}


/** Installs the manipulators to show for selected items. */
inline void Mouse::addManipulators() {
	
	// Add
	add(new Manipulator('x', Command::TRANSLATE_X, "ui/TranslateX.xml"));
	add(new Manipulator('y', Command::TRANSLATE_Y, "ui/TranslateY.xml"));
	add(new Manipulator('z', Command::TRANSLATE_Z, "ui/TranslateZ.xml"));
	add(new Manipulator('x', Command::SCALE_X, "ui/ScaleX.xml", 2));
	add(new Manipulator('y', Command::SCALE_Y, "ui/ScaleY.xml", 2));
	add(new Manipulator('z', Command::SCALE_Z, "ui/ScaleZ.xml", 2));
}

#endif
