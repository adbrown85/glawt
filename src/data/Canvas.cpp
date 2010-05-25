/*
 * Canvas.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Canvas.hpp"


/** Initializes the widget. */
Canvas::Canvas(int width, int height) {
	
	// Size
	this->width = width;
	this->height = height;
	set_size_request(width, height);
	
	// Events
	add_events(Gdk::KEY_PRESS_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::SCROLL_MASK);
	
	// View
	position = Vector(0.0,0.0,CANVAS_ZOOM,1.0);
	
	// Callbacks
	display = NULL;
	drag = NULL;
	mouse = NULL;
	keyboard = NULL;
	setup = NULL;
	
	// Capability
	mode = Gdk::GL::MODE_RGBA | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE;
	glConfig = Gdk::GL::Config::create(mode);
	if (!glConfig) {
		throw "[Canvas] Cannot find an OpenGL-capable visual.";
	}
	set_gl_capability(glConfig);
}


/** Applies the camera position and rotation to the OpenGL modelview matrix. */
void Canvas::applyView() {
	
	float rotationArray[16];
	
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Position
	glTranslatef(position.x, position.y, position.z);
	
	// Rotation
	rotation.getMatrix().toArray(rotationArray);
	glMultMatrixf(rotationArray);
}


/** Initializes the windowing system. */
void Canvas::init(int argc, char *argv[]) {
	
	Gtk::GL::init(argc, argv);
}


/** Initializes OpenGL. */
void Canvas::on_realize() {
	
	Gtk::GL::DrawingArea::on_realize();
	
	// Store pointers
	glContext = get_gl_context();
	glDrawable = get_gl_drawable();
	glWindow = get_gl_window();
	window = get_window();
	
	// Focus
	set_can_focus(true);
	grab_focus();
	
	// Start of OpenGL calls
	begin();
	
	// Enable options
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Set up viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
	
	// End of OpenGL calls
	end();
}


/** Widget needs to be redrawn. */
bool Canvas::on_expose_event(GdkEventExpose *event) {
	
	// Start
	begin();
	
	// Run callback
	(*display)();
	
	// Finish
	end();
	return true;
}


/** Checks if there were any OpenGL errors. */
void Canvas::check() {
	
	GLenum error;
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << gluErrorString(error) << endl;
	}
}


/** When a mouse button is pressed.
 * 
 * Consider having it call grab_focus() so key presses will affect it.
 * 
 * Important parts of GdkEventButton are:
 *     button  Button that was pressed (1-left, 2-middle, 3-right)
 *     x       X location of the pointer relative to the widget
 *     y       Y location of the pointer relative to the widget (top=0)
 *     state   Bitmask state of modifier keys and buttons (GdkModifierType)
 */
bool Canvas::on_button_press_event(GdkEventButton *event) {
	
	// Update button
	mouseButton = event->button;
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	mouseButtonPressed = true;
	if (mouse != NULL) {
		(*mouse)(mouseButton, CANVAS_DOWN, event->x, event->y);
	}
	return true;
}


/** When a mouse button is released.
 * 
 * @see on_button_press_event
 */
bool Canvas::on_button_release_event(GdkEventButton *event) {
	
	// Update
	mouseButton = event->button;
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	mouseButtonPressed = false;
	if (mouse != NULL) {
		(*mouse)(mouseButton, CANVAS_UP, event->x, event->y);
	}
	return true;
}


/** Note this usually should return true so the event is consumed.
 * 
 * That way if one of the arrow keys is pressed GTK doesn't change the focus to 
 * another widget.
 */
bool Canvas::on_key_press_event(GdkEventKey *event) {
	
	// Update
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	if (keyboard != NULL) {
		(*keyboard)(event->keyval, lastMouseX, lastMouseY);
	}
	return true;
}


/** When the mouse moves in the widget.
 * 
 * Because there is no distinct dragging event, we just return if no button 
 * is pressed.  Because here we're listening for both button_press and
 * button_release events and keeping track of the mouse state on each one, 
 * we could just use that.
 * 
 * Also, to avoid some unintened drags, we return if not enough time has passed 
 * between when the mouse was clicked and when the mouse is moved.  The value 
 * could be adjusted depending on your taste.
 * 
 * Lastly, if the user drags past the widget boundaries the widget will still 
 * receive the values.  For that reason this method may receive values outside 
 * of its allocation.  In fact, if the user moves above or to the left of the
 * widget it will receive negative values.
 * 
 * Important parts of GdkEventMotion are:
 *     x      X location of the pointer relative to the widget
 *     y      Y location of the pointer relative to the widget (top=0)
 *     state  Bitmask state of modifier keys and buttons (GdkModifierType)
 */
bool Canvas::on_motion_notify_event(GdkEventMotion *event) {
	
	// Check if event should be discarded
	if (!mouseButtonPressed) {
		return false;
	} if ((event->time - lastMouseMotionEventTime) < 10) {
		return false;
	}
	
	// Update
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	if (drag != NULL) {
		(*drag)(event->x, event->y);
		lastMouseMotionEventTime = event->time;
	}
	return false;
}


/** When the user scrolls the mouse wheel in the widget.
 * 
 * Important parts of GdkEventScroll are:
 *     direction  One of GDK_SCROLL_{UP|DOWN|LEFT|RIGHT}
 *     state      Bitmask state of modifier keys and buttons (GdkModifierType)
 */
bool Canvas::on_scroll_event(GdkEventScroll *event) {
	
	// Update
	updateModifer(event->state);
	if (event->direction == GDK_SCROLL_UP) {
		mouseWheel = CANVAS_WHEEL_UP;
	} else {
		mouseWheel = CANVAS_WHEEL_DOWN;
	}
	
	// Run callback
	grab_focus();
	if (mouse != NULL) {
		(*mouse)(mouseWheel, CANVAS_UP, event->x, event->y);
	}
	return false;
}


/** Resets the canvas's rotation and position. */
void Canvas::reset() {
	
	// Reset transformations
	position.set(0.0, 0.0, CANVAS_ZOOM);
	rotation.set(0.0, Vector(0.0,1.0,0.0));
	refresh();
}


/** Rotates the camera by axis/angle. */
void Canvas::rotate(float angle, const Vector &axis) {
	
	rotation.rotate(angle, axis);
	refresh();
}


/** Moves the camera. */
void Canvas::translate(const Vector &move) {
	
	position += move;
	refresh();
}


void Canvas::updateModifer(guint state) {
	
	if (state & GDK_CONTROL_MASK) {
		modifier = CANVAS_MOD_CONTROL;
	} else if (state & GDK_SHIFT_MASK) {
		modifier = CANVAS_MOD_SHIFT;
	} else if (state & GDK_MOD1_MASK) {
		modifier = CANVAS_MOD_ALT;
	} else {
		modifier = 0;
	}
}

