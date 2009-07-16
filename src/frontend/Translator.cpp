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
	
	// Initialize 
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
}



/**
 * Draws the Translator.
 */
void Translator::draw() const {
	
	// Set unique color for each translator based on axis
	glColor3f(axis.x, axis.y, axis.z);
	
	// Line from origin
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(axis.x*size, axis.y*size, axis.z*size);
	glEnd();
	
	// Cone at end of line
	glPushMatrix();
		glTranslatef(axis.x*size, axis.y*size, axis.z*size);
		if (axis.x >= 0.9)
			glRotatef(90.0, 0.0, 1.0, 0.0);
		else if (axis.y >= 0.9)
			glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(cyl, 0.1, 0, 0.25, 12, 1);
	glPopMatrix();
}



/**
 * Use the Translator.
 * 
 * @param movement
 *     Difference between current and last cursor positions.
 */
void Translator::use(Scene *scene, const Vector &movement) {
	
	float dotProduct, translateAmount;
	Matrix rotationMatrix;
	ShapePtrSet::iterator si;
	Translation *translation;
	Vector viewAxis;
	
	// Calculate translate amount from movement and view axis
	rotationMatrix = scene->getRotationMatrix();
	viewAxis = rotationMatrix * axis;
	dotProduct = movement.getNormalized().dotProduct(viewAxis.getNormalized());
	translateAmount = movement.length() * dotProduct * 0.0125;
	
	// Add translate amount to position of each selected shape
	if (fabs(dotProduct) > 0.75) {
		for (si=scene->selection.begin();
		     si!=scene->selection.end();
		     ++si) {
			translation = (*si)->translation;
			if (translation != NULL) {
				if (axis.x > 0.9)
					translation->x += translateAmount;
				else if (axis.y > 0.9)
					translation->y += translateAmount;
				else if (axis.z > 0.9)
					translation->z += translateAmount;
			}
		}
	}
}
