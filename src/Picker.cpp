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
 * Choose the item to return.  Manipulators are returned before shapes, and if 
 * more than one shape is picked, the closest one to the camera is chosen.
 */
GLuint Picker::choose(Scene *scene) {
	
	float closestDepth=-123456789.0;
	GLuint closestID;
	Item *item;
	Matrix rotationMatrix;
	set<GLuint>::iterator ii;
	Vector viewPosition;
	
	// Check for manipulator
	for (ii=ids.begin(); ii!=ids.end(); ++ii) {
		item = Item::find(*ii);
		if (typeid(*item) == typeid(Translator))
			return item->getID();
	}
	
	// Otherwise find closest to screen
	rotationMatrix = scene->getRotationMatrix();
	for (ii=ids.begin(); ii!=ids.end(); ++ii) {
		item = Item::find(*ii);
		viewPosition = rotationMatrix * item->getPosition();
		if (viewPosition.z > closestDepth) {
			closestDepth = viewPosition.z;
			closestID = item->getID();
		}
	}
	return closestID;
}



/**
 * Draws the items.  Make sure this matches up with how Display draws the 
 * items.  It may be a good idea to abstract this out to a Painter class, or
 * something like that.
 */
void Picker::draw(Scene *scene,
                  vector<Manipulator*> manipulators) {
	
	float rotationMatrixArray[16];
	int count;
	Item *item;
	Matrix rotationMatrix;
	
	// Initialize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Transform
	glTranslatef(scene->position.x, scene->position.y, scene->position.z);
	rotationMatrix = scene->getRotationMatrix();
	rotationMatrix.getArray(rotationMatrixArray);
	glMultMatrixf(rotationMatrixArray);
	
	// Draw each item that's not hidden
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		item = scene->items[i];
		if (item->isShown()) {
			glPushName(item->getID());
			item->draw();
			if (item->isSelected()) {
				for (int i=0; i<manipulators.size(); i++) {
					glPushName(manipulators[i]->getID());
					manipulators[i]->copy(*item);
					manipulators[i]->draw();
				}
			}
		}
	}
}



/**
 * Restores the original projection matrix.
 */
void Picker::finish() {
	
	// Restore
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
}



/**
 * Initializes the pick buffer.
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
 * Picks an item from a scene.
 */
GLuint Picker::pick(Scene *scene,
                    vector<Manipulator*> manipulators,
                    int x,
                    int y) {
	
	// Pick an item
	initialize(x, y);
	draw(scene, manipulators);
	store();
	
	// Return
	finish();
	if (ids.empty())
		return 0;
	else if (ids.size() == 1)
		return *(ids.begin());
	else
		return choose(scene);
}



/**
 * Stores the IDs of the items picked.
 */
void Picker::store() {
	
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
