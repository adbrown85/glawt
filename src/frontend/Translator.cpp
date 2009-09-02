/*
 * Translator.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Translator.hpp"



/**
 * Creates a new Translator using an axis.
 */
Translator::Translator(float x, float y, float z) {
	
	// Initialize attributes
	axis.set(x, y, z, 1.0);
	size = 1.0;
	
	// Initialize GLU shapes
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_FILL);
}



/**
 * Draws the Translator.
 */
void Translator::draw() const {
	
	float half;
	
	// Set unique color for each translator based on axis
	glColor3f(axis.x, axis.y, axis.z);
	
	// Line from origin
	half = size / 2;
	glBegin(GL_LINES);
		glVertex3f(axis.x*half, axis.y*half, axis.z*half);
		glVertex3f(axis.x*size, axis.y*size, axis.z*size);
	glEnd();
	
	// Cone at end of line
	glPushMatrix();
		glTranslatef(axis.x*size, axis.y*size, axis.z*size);
		if (axis.x >= 0.9)
			glRotatef(90.0, 0.0, 1.0, 0.0);
		else if (axis.y >= 0.9)
			glRotatef(-90.0, 1.0, 0.0, 0.0);
		glPushMatrix();
			glRotatef(180.0, 0.0, 1.0, 0.0);
			gluDisk(disk, 0.0, 0.1, 12, 1);
		glPopMatrix();
		gluCylinder(cone, 0.1, 0, 0.25, 12, 1);
	glPopMatrix();
}



/**
 * Use the Translator.
 * 
 * @param scene
 *     Graph of nodes.
 * @param movement
 *     Difference between current and last cursor positions.
 */
void Translator::use(Scene *scene,
                     const Vector &movement) {
	
	float dotProduct, translateAmount;
	Matrix rotationMatrix;
	Selection::iterator si;
	Translation *translation;
	Vector viewAxis;
	
	// Calculate translate amount from movement and view axis
	rotationMatrix = scene->getRotationMatrix();
	viewAxis = rotationMatrix * axis;
	dotProduct = movement.getNormalized().dotProduct(viewAxis.getNormalized());
	translateAmount = movement.length() * dotProduct * 0.02;
	
	// Translate selection
	if (fabs(dotProduct) > 0.75) {
		if (axis.x > 0.9)
			delegate->run(Command::TRANSLATE_X, translateAmount);
		else if (axis.y > 0.9)
			delegate->run(Command::TRANSLATE_Y, translateAmount);
		else
			delegate->run(Command::TRANSLATE_Z, translateAmount);
	}
}
