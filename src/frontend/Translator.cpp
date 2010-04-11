/*
 * Translator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
	glPushAttrib(GL_CURRENT_BIT);
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
	
	// Restore color
	glPopAttrib();
}



/**
 * Calculates how a pixel compares to a global unit.
 * 
 * @param scene
 *     Graph of nodes.
 * @param shapeID
 *     ID of the shape to use for the depth component.
 */
float Translator::findPixelFactor(Scene *scene,
                                  GLuint shapeID) {
	
	float screenX, projMatArr[16];
	float pixelsPerUnit, viewDepth;
	Matrix projMat;
	Node *node;
	Vector clipVec, projVec, viewVec;
	
	// Get depth
	node = dynamic_cast<Node*>(Identifiable::findByID(shapeID));
	viewDepth = node->getDepth() + scene->position.z;
	
	// Get projection matrix
	glGetFloatv(GL_PROJECTION_MATRIX, projMatArr);
	projMat.set(projMatArr);
	
	// Transform vector from view to clip space
	viewVec.set(1.0, 0.0, viewDepth, 1.0);
	projVec = projMat * viewVec;
	clipVec = projVec / projVec.w;
	
	// Calculate pixels per unit
	screenX = ((clipVec.x + 1.0) * 0.5) * scene->getWidth();
	pixelsPerUnit = screenX - (scene->getWidth() * 0.5);
	return 1 / pixelsPerUnit;
}



/**
 * Use the Translator.
 * 
 * @param scene
 *     Graph of nodes.
 * @param movement
 *     Difference between current and last cursor positions.
 * @param shapeID
 *     ID of the shape the translator is attached to.
 */
void Translator::use(Scene *scene,
                     const Vector &movement,
                     GLuint shapeID) {
	
	float dotProduct, pixelFactor, translateAmount;
	Matrix rotationMatrix;
	Vector viewAxis;
	
	// Calculate translate amount
	pixelFactor = findPixelFactor(scene, shapeID);
	rotationMatrix = scene->getRotationMatrix();
	viewAxis = rotationMatrix * axis;
	dotProduct = movement.getNormalized().dotProduct(viewAxis.getNormalized());
	translateAmount = movement.length() * dotProduct * pixelFactor;
	
	// Translate selection
	if (fabs(dotProduct) > 0.5) {
		if (axis.x > 0.9)
			delegate->run(Command::TRANSLATE_X, translateAmount);
		else if (axis.y > 0.9)
			delegate->run(Command::TRANSLATE_Y, translateAmount);
		else
			delegate->run(Command::TRANSLATE_Z, translateAmount);
	}
}
