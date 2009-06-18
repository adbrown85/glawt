/*
 * Translator.cpp
 *     Visual tool for moving items.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Translator.hpp"



void Translator::draw() const {
	
	// Move into position
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	
		// Lines
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(1.0*size, 0.0, 0.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0*size);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0*size, 0.0);
		glEnd();
		
		// X cone
		glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(1.0*size, 0.0, 0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			gluCylinder(cyl, 0.1, 0, 0.25, 12, 1);
		glPopMatrix();
		
		// Y cone
		glPushMatrix();
			glColor3f(0.0, 1.0, 0.0);
			glTranslatef(0.0, 1.0*size, 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cyl, 0.1, 0, 0.25, 12, 1);
		glPopMatrix();
		
		// Z cone
		glPushMatrix();
			glColor3f(0.0, 0.0, 1.0);
			glTranslatef(0.0, 0.0, 1.0*size);
			glRotatef(0.0, 0.0, 1.0, 0.0);
			gluCylinder(cyl, 0.1, 0, 0.25, 12, 1);
		glPopMatrix();
	glPopMatrix();
}
