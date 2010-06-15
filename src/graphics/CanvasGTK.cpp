/*
 * CanvasGTK.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CanvasGTK.hpp"
#ifdef HAVE_GTK


/** Initializes the widget. */
CanvasGTK::CanvasGTK(int width, int height) : Canvas(width,height) {
	
	// Size
	set_size_request(width, height);
	
	// Events
	add_events(Gdk::KEY_PRESS_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::SCROLL_MASK);
	
	// Capability
	mode = Gdk::GL::MODE_RGBA | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE;
	glConfig = Gdk::GL::Config::create(mode);
	if (!glConfig) {
		throw "[CanvasGTK] Cannot find an OpenGL-capable visual.";
	}
	set_gl_capability(glConfig);
}


/** Initializes OpenGL. */
void CanvasGTK::on_realize() {
	
	Gtk::GL::DrawingArea::on_realize();
	
	// Store pointers
	glContext = get_gl_context();
	glDrawable = get_gl_drawable();
	glWindow = get_gl_window();
	window = get_window();
	
	// Focus
	set_flags(Gtk::CAN_FOCUS);
	grab_focus();
	
	// Start
	begin();
	
	// Camera and type
	getCamera()->load(getWidth(), getHeight());
	typeface.load("courier 8");
	
	// Finish
	end();
}


/** Widget needs to be redrawn. */
bool CanvasGTK::on_expose_event(GdkEventExpose *event) {
	
	begin();
	fireEvent(CanvasEvent::DISPLAY);
	end();
	return true;
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
bool CanvasGTK::on_button_press_event(GdkEventButton *event) {
	
	// Update
	state.x = event->x;
	state.y = event->y;
	state.combo.trigger = event->button;
	state.combo.action = CANVAS_DOWN;
	updateModifer(event->state);
	isMouseButtonPressed = true;
	
	// Fire event
	grab_focus();
	fireEvent(CanvasEvent::BUTTON);
	return true;
}


/** When a mouse button is released.
 * 
 * @see on_button_press_event
 */
bool CanvasGTK::on_button_release_event(GdkEventButton *event) {
	
	// Update
	state.x = event->x;
	state.y = event->y;
	state.combo.trigger = event->button;
	state.combo.action = CANVAS_UP;
	updateModifer(event->state);
	isMouseButtonPressed = false;
	
	// Fire event
	grab_focus();
	fireEvent(CanvasEvent::BUTTON);
	return true;
}


/** When a key is pressed.
 * 
 * @note This should usually return true so the event is consumed. That way if 
 * one of the arrow keys is pressed GTK doesn't change the focus to another 
 * widget.
 */
bool CanvasGTK::on_key_press_event(GdkEventKey *event) {
	
	// Update
	state.combo.trigger = event->keyval;
	state.combo.action = CANVAS_DOWN;
	updateModifer(event->state);
	
	// Fire event
	grab_focus();
	fireEvent(CanvasEvent::KEY);
	return true;
}


bool CanvasGTK::on_idle() {
	
	fireEvent(CanvasEvent::DISPLAY);
	refresh();
	window->process_updates(false);
}


bool CanvasGTK::on_map_event(GdkEventAny *event) {
	
	started = true;
	if (automaticallyRefresh) {
		connectIdle();
	}
	return true;
}


void CanvasGTK::connectIdle() {
	
	if (!idle.connected()) {
		glog << "[CanvasGTK] Connecting idle function." << endl;
		idle = Glib::signal_idle().connect(
			sigc::mem_fun(*this, &CanvasGTK::on_idle), GDK_PRIORITY_REDRAW
		);
	}
}


void CanvasGTK::disconnectIdle() {
	
	if (idle.connected()) {
		glog << "[CanvasGTK] Disconnecting idle function." << endl;
		idle.disconnect();
	}
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
bool CanvasGTK::on_motion_notify_event(GdkEventMotion *event) {
	
	// Update
	state.x = event->x;
	state.y = event->y;
	
	// Check if just moving
	if (!isMouseButtonPressed) {
		return false;
	}
	
	// Update
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	fireEvent(CanvasEvent::DRAG);
	return false;
}


/** When the user scrolls the mouse wheel in the widget.
 * 
 * Important parts of GdkEventScroll are:
 *     direction  One of GDK_SCROLL_{UP|DOWN|LEFT|RIGHT}
 *     state      Bitmask state of modifier keys and buttons (GdkModifierType)
 */
bool CanvasGTK::on_scroll_event(GdkEventScroll *event) {
	
	// Update
	if (event->direction == GDK_SCROLL_UP) {
		state.combo.trigger = CANVAS_WHEEL_UP;
	} else {
		state.combo.trigger = CANVAS_WHEEL_DOWN;
	}
	updateModifer(event->state);
	
	// Run callback
	grab_focus();
	fireEvent(CanvasEvent::BUTTON);
	return false;
}


/** Determines if events should be continuously sent to display listeners. */
void CanvasGTK::setAutomaticallyRefresh(bool automaticallyRefresh) {
	
	this->automaticallyRefresh = automaticallyRefresh;
	if (started && automaticallyRefresh) {
		connectIdle();
	} else {
		disconnectIdle();
	}
}


/** Assigns the modifer according to the state of a GDK event. */
void CanvasGTK::updateModifer(guint state) {
	
	if (state & GDK_CONTROL_MASK) {
		this->state.combo.modifier = CANVAS_MOD_CONTROL;
	} else if (state & GDK_SHIFT_MASK) {
		this->state.combo.modifier = CANVAS_MOD_SHIFT;
	} else if (state & GDK_MOD1_MASK) {
		this->state.combo.modifier = CANVAS_MOD_ALT;
	} else {
		this->state.combo.modifier = CANVAS_MOD_NONE;
	}
}


void CanvasGTK::write(const string &text, int x, int y) {
	
	float xf, yf;
	int viewport[4];
	
	// Calculate position
	glGetIntegerv(GL_VIEWPORT, viewport);
	xf = ((float)viewport[2] - x) / viewport[2];
	yf = ((float)viewport[3] - y) / viewport[3];
	
	// Set position
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-xf, yf);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// Draw text
	typeface.write(text);
}


#endif
