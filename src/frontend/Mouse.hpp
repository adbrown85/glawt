/*
 * Mouse.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "common.h"
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
	void dragApply();
	void dragDecide();
	void enableScaleManipulators();
	void enableTranslateManipulators();
	float findDragAmount(int i);
	void pickItem();
	bool useUnconstrained(int command);
private:
	Binding *binding, *dragBindings[2];
	CanvasState state, last;
	GLuint itemID, shapeID;
	Manipulator *manip;
	Vector axis, direction, movement;
	Picker picker;
	int iteration, index;
};


/** Installs the bindings for the mouse. */
inline void Mouse::addBindings() {
	
	Combo combo;
	
	// Mouse wheel up
	combo.trigger = CANVAS_WHEEL_UP;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_UP;
	add(Binding(combo, Command::ZOOM_IN, 0.5f));
	
	// Mouse wheel down
	combo.trigger = CANVAS_WHEEL_DOWN;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_UP;
	add(Binding(combo, Command::ZOOM_OUT, 0.5f));
	
	// Ctrl + Left button
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_CONTROL;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::GRAB, &itemID));
	
	// Left button drag in x
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'x';
	add(Binding(combo, Command::CIRCLE_Y, -1.5f));
	
	// Left button drag in y
	combo.trigger = CANVAS_LEFT_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'y';
	add(Binding(combo, Command::CIRCLE_X, -1.5f));
	
	// Middle button drag in x
	combo.trigger = CANVAS_MIDDLE_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'x';
	add(Binding(combo, Command::TRACK, -0.8f));
	
	// Middle button drag in y
	combo.trigger = CANVAS_MIDDLE_BUTTON;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = 'y';
	add(Binding(combo, Command::BOOM, 0.8f));
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


/** Commands that should not be constrained to one axis. */
inline bool Mouse::useUnconstrained(int command) {
	
	return (command == Command::BOOM) || (command == Command::TRACK);
}


#endif
