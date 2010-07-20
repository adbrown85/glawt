/*
 * CanvasGLUT.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CanvasGLUT.hpp"
#ifdef HAVE_GLUT
CanvasGLUT *CanvasGLUT::instance=NULL;


CanvasGLUT::CanvasGLUT(int width, int height) : Canvas(width,height) {
	
	// Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	// Store instance
	instance = this;
}


GLuint CanvasGLUT::getElapsedTime() {
	
	return glutGet(GLUT_ELAPSED_TIME);
}


void CanvasGLUT::display(void) {
	
	instance->fireEvent(CanvasEvent::DISPLAY);
}


void CanvasGLUT::mouse(int button, int state, int x, int y) {
	
	// Update
	instance->state.x = x;
	instance->state.y = y;
	instance->state.combo.trigger = button;
	switch (state) {
	case GLUT_DOWN:
		instance->state.combo.action = CANVAS_DOWN;
		instance->isMouseButtonPressed = true;
		break;
	case GLUT_UP:
		instance->state.combo.action = CANVAS_UP;
		instance->isMouseButtonPressed = false;
	}
	instance->updateModifier();
	
	// Fire event
	instance->fireEvent(CanvasEvent::BUTTON);
}


void CanvasGLUT::keyboard(unsigned char key, int x, int y) {
	
	// Update
	instance->state.x = x;
	instance->state.y = y;
	instance->state.combo.trigger = key;
	instance->state.combo.action = CANVAS_DOWN;
	instance->updateModifier();
	
	// Fire event
	instance->fireEvent(CanvasEvent::KEY);
}


void CanvasGLUT::motion(int x, int y) {
	
	// Update
	instance->state.x = x;
	instance->state.y = y;
	
	// Fire event
	instance->fireEvent(CanvasEvent::DRAG);
}


void CanvasGLUT::special(int key, int x, int y) {
	
	// Filter
	switch (key) {
	case GLUT_KEY_UP: key = CANVAS_KEY_UP; break;
	case GLUT_KEY_RIGHT: key = CANVAS_KEY_RIGHT; break;
	case GLUT_KEY_DOWN: key = CANVAS_KEY_DOWN; break;
	case GLUT_KEY_LEFT: key = CANVAS_KEY_LEFT; break;
	default: break;
	}
	
	// Update
	instance->state.x = x;
	instance->state.y = y;
	instance->state.combo.trigger = key;
	instance->state.combo.action = CANVAS_DOWN;
	instance->updateModifier();
	
	// Fire event
	instance->fireEvent(CanvasEvent::KEY);
}


void CanvasGLUT::updateModifier() {
	
	int modifier=glutGetModifiers();
	
	// Adjust and store modifier
	if (modifier & GLUT_ACTIVE_CTRL) {
		this->state.combo.modifier = CANVAS_MOD_CONTROL;
	} else if (modifier & GLUT_ACTIVE_ALT) {
		this->state.combo.modifier = CANVAS_MOD_ALT;
	} else if (modifier & GLUT_ACTIVE_SHIFT) {
		this->state.combo.modifier = CANVAS_MOD_SHIFT;
	} else {
		this->state.combo.modifier = CANVAS_MOD_NONE;
	}
}


void CanvasGLUT::onRealize() {
	
	// Camera
	getCamera()->load(getWidth(), getHeight());
	
	// Register callbacks
	glutDisplayFunc(&display);
	glutMouseFunc(&mouse);
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(&special);
	glutMotionFunc(&motion);
	
	// Load extensions
	Extensions::load();
}


void CanvasGLUT::write(const string &text, int x, int y) {
	
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
	for (size_t i=0; i<text.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
}



#endif // HAVE_GLUT
