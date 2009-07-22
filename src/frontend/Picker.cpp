/*
 * Picker.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Picker.hpp"
GLuint Picker::buf[PICK_BUFFER_SIZE];
set<GLuint> Picker::ids;



/**
 * Choose the item to return.
 * 
 * Manipulators are returned before shapes, and if more than one shape is 
 * picked, the closest one to the camera is chosen.
 */
GLuint Picker::chooseItem(Scene *scene) {
	
	float closestDepth=-123456789.0;
	GLuint closestID;
	Identifiable *identifiable;
	Matrix rotationMatrix;
	set<GLuint>::iterator ii;
	Vector viewPosition;
	
	// Check for manipulator
	for (ii=ids.begin(); ii!=ids.end(); ++ii) {
		identifiable = Identifiable::findByID(*ii);
		if (dynamic_cast<Manipulator*>(identifiable))
			return identifiable->getID();
	}
	
	// Otherwise find closest to screen
	rotationMatrix = scene->getRotationMatrix();
	for (ii=ids.begin(); ii!=ids.end(); ++ii) {
/*
		identifiable = Item::find(*ii);
		viewPosition = rotationMatrix * identifiable->getPosition();
		if (viewPosition.z > closestDepth) {
			closestDepth = viewPosition.z;
			closestID = identifiable->getID();
		}
		closestID = identifiable->getID();
*/
		closestID = (*ii);
	}
	return closestID;
}



/**
 * Restores the original projection matrix.
 * 
 * @warning Not sure if glFlush is really needed here.
 */
void Picker::finish() {
	
	// Restore
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// glFlush();
}



/**
 * Initializes the viewport, pick buffer, and projection matrix.
 */
void Picker::initialize(int x, int y) {
	
	GLint width, height, viewport[4];
	
	// Get size of render viewport
	glGetIntegerv(GL_VIEWPORT, viewport);
	width = viewport[2];
	height = viewport[3];
	
	// Create storage
	glSelectBuffer(PICK_BUFFER_SIZE, buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	ids.clear();
	
	// Save render projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	// Setup the viewport for the pick buffer
	gluPickMatrix((GLdouble)x, (GLdouble)height-y, 5.0, 5.0, viewport);
	gluPerspective(30.0, (float)width/height, 0.1, 1000.0);
}



/**
 * Picks an item from a scene
 * 
 * @return ID number of the item picked.  UINT_MAX if nothing.
 */
GLuint Picker::pick(Scene *scene,
                    vector<Manipulator*> &manipulators,
                    int x,
                    int y) {
	
	// Pick an item
	initialize(x, y);
	Painter::paint(*scene, manipulators, GL_SELECT);
	finish();
	storeIDsOfItems();
	
	// Return
	if (ids.empty())
		return UINT_MAX;
	else if (ids.size() == 1)
		return *(ids.begin());
	else
		return chooseItem(scene);
}



/**
 * Stores the IDs of the items picked.
 */
void Picker::storeIDsOfItems() {
	
	GLuint id, pos, *ptr;
	GLint count;
	set<GLuint>::iterator ii;
	
	// Get number of items picked
	count = glRenderMode(GL_RENDER);
	
	// Get ID of each item from its position in stack
	ptr = buf;
	for (int i=0; i<count; i++) {
		pos = *ptr;
		ptr += 3;
		for (int j=0; j<pos; j++) {
			id = *ptr;
			ptr++;
		}
		ids.insert(id);
	}
}
