/*
 * Picker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Picker.hpp"


Picker::Picker(Scene *scene, Canvas *canvas) {
	
	// Initialize fields
	this->scene = scene;
	this->canvas = canvas;
	this->painter = new Painter(canvas, scene);
	this->painter->setMode(GL_SELECT);
}


void Picker::addManipulators(list<Manipulator*> manips) {
	
	list<Manipulator*>::iterator it;
	
	for (it=manips.begin(); it!=manips.end(); ++it) {
		painter->addManipulator(*it);
	}
}


/** Choose the item to return.
 * 
 * Manipulators are returned before shapes, and if more than one shape is 
 * picked, the closest one to the camera is chosen.
 */
pair<GLuint,GLuint> Picker::chooseItem() {
	
	float depth, closestDepth;
	Identifiable *identifiable;
	Matrix rotation;
	Shape *shape;
	map<GLuint,GLuint>::iterator pi;
	pair<GLuint,GLuint> closestPair;
	
	// Check for manipulator
	for (pi=ids.begin(); pi!=ids.end(); ++pi) {
		identifiable = Identifiable::findByID(pi->first);
		if (dynamic_cast<Manipulator*>(identifiable))
			return *pi;
	}
	
	// Otherwise find closest to screen
	closestDepth = FLT_MIN;
	rotation = canvas->getCamera()->getRotation();
	for (pi=ids.begin(); pi!=ids.end(); ++pi) {
		identifiable = Identifiable::findByID(pi->first);
		shape = dynamic_cast<Shape*>(identifiable);
		if (shape == NULL)
			break;
		depth = (rotation * shape->getPosition()).z;
		if (depth > closestDepth) {
			closestDepth = depth;
			closestPair = *pi;
		}
	}
	return closestPair;
}


/** Restores the original projection matrix. */
void Picker::finish() {
	
	// Restore
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}


/** Initializes the viewport, pick buffer, and projection matrix. */
void Picker::initialize(int x, int y) {
	
	GLint height, width, viewport[4];
	
	// Get size of render viewport
	glGetIntegerv(GL_VIEWPORT, viewport);
	width = viewport[2];
	height = viewport[3];
	
	// Create storage
	glSelectBuffer(PICK_BUFFER_SIZE, buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	ids.clear();
	
	// Save render projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	// Setup the viewport for the pick buffer
	gluPickMatrix((GLdouble)x, (GLdouble)height-y, 5.0, 5.0, viewport);
	gluPerspective(30.0, (float)width/height, 0.1, 1000.0);
}


/** @return ID of item picked and shape it belongs to (UINT_MAX if nothing). */
pair<GLuint,GLuint> Picker::pick(int x, int y) {
	
	// Pick an item
	initialize(x, y);
	painter->start();
	finish();
	storeIDsOfItems();
	
	// Return
	if (ids.empty())
		return pair<GLuint,GLuint>(UINT_MAX, UINT_MAX);
	else if (ids.size() == 1)
		return *(ids.begin());
	else
		return chooseItem();
}


/** Stores the IDs of the items picked.
 * 
 * A hit record is made up of at least four unsigned integers in the 
 * selection buffer, as shown below.  There will be one hit record for each 
 * item under the mouse cursor.  The exact number is returned by glRenderMode 
 * when switching back to GL_RENDER.
 * 
 * The first integer in a hit record is the number of IDs that were on the name 
 * stack when the item was drawn, which should always be one.  The second and 
 * third values are the minimum and maximum depth values at the time.  Finally, 
 * the IDs that were present on the name stack when the item was drawn are 
 * listed from bottom to top.  In other words, the item under the cursor will 
 * be the nth item in the list, where n is equal to the number of IDs.
 *   -------------
 *   | numOfIDs  |
 *   | minDepth  |
 *   | maxDepth  |
 *   | ids       |
 *   |    ...    |
 *   -------------
 * 
 * @throws Exception if a hit record with 0 item IDs was detected.
 */
void Picker::storeIDsOfItems() {
	
	GLuint id, numOfIDs, *ptr, shapeID;
	GLint numOfHitRecords;
	
	// Get number of items picked
	numOfHitRecords = glRenderMode(GL_RENDER);
	
	// For each hit record
	ptr = buf;
	for (int i=0; i<numOfHitRecords; ++i) {
		
		// Get number of IDs in name stack
		numOfIDs = *ptr;
		if (numOfIDs == 0)
			throw Exception("[Picker] Hit record with 0 item IDs detected!");
		
		// Find ID of shape that was drawn
		ptr += 3;
		shapeID = *ptr;
		
		// Record item picked with shape it was attached to
		for (size_t j=0; j<numOfIDs; ++j) {
			id = *ptr;
			ptr++;
		}
		ids.insert(pair<GLuint,GLuint>(id, shapeID));
	}
}

