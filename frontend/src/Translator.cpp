/*
 * Translator.cpp
 *     Visual tool for moving shapes.
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
	type = "Translator";
	
	// Initialize 
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
}



/**
 * Draws the Translator.
 */
void Translator::draw() const {
	
	// Move into position
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
		
		// Color
		glColor3f(axis.x, axis.y, axis.z);
		
		// Line
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(axis.x*size, axis.y*size, axis.z*size);
		glEnd();
		
		// Cone
		glPushMatrix();
			glTranslatef(axis.x*size, axis.y*size, axis.z*size);
			if (axis.x >= 0.9)
				glRotatef(90.0, 0.0, 1.0, 0.0);
			else if (axis.y >= 0.9)
				glRotatef(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cyl, 0.1, 0, 0.25, 12, 1);
		glPopMatrix();
		
		glPopMatrix();
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
	int numberOfItems;
	Item *item;
	Matrix rotationMatrix;
	Vector position, viewAxis;
	
	// Calculate translate amount from movement and view axis
	rotationMatrix = scene->getRotationMatrix();
	viewAxis = rotationMatrix * axis;
	dotProduct = movement.getNormalized().dotProduct(viewAxis.getNormalized());
	translateAmount = movement.length() * dotProduct * 0.0125;
	
	// Add translate amount to position of each selected item
	if (fabs(dotProduct) > 0.75) {
		numberOfItems = scene->items.size();
		for (int i=0; i<numberOfItems; i++) {
			item = scene->items[i];
			if (item->isSelected()) {
				position = item->getPosition();
				if (axis.x > 0.9)
					position.x += translateAmount;
				else if (axis.y > 0.9)
					position.y += translateAmount;
				else if (axis.z > 0.9)
					position.z += translateAmount;
				item->setPosition(position.x, position.y, position.z);
			}
		}
	}
}
