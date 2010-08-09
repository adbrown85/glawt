/*
 * State.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "State.hpp"


void State::apply(Matrix &matrix) {
	
	GLfloat array[16];
	
	matrix.toArray(array);
	glMultMatrixf(array);
}


void State::getIdentityMatrix(GLfloat array[16]) {
	
	Matrix matrix;
	
	matrix.toArray(array);
}


Matrix State::getModelViewMatrix() {
	
	GLfloat array[16];
	Matrix matrix;
	
	glGetFloatv(GL_MODELVIEW_MATRIX, array);
	matrix.set(array);
	return matrix;
}


Matrix State::getModelViewProjectionMatrix() {
	
	Matrix mvMatrix, pMatrix;
	
	mvMatrix = getModelViewMatrix();
	pMatrix = getProjectionMatrix();
	return pMatrix * mvMatrix;
}


void State::getModelViewProjectionMatrix(GLfloat array[16]) {
	
	Matrix mvpMatrix;
	
	mvpMatrix = getModelViewProjectionMatrix();
	mvpMatrix.toArray(array);
}


Matrix State::getNormalMatrix() {
	
	return getModelViewMatrix().getInverse().getTranspose();
}


void State::getNormalMatrix(GLfloat array[9]) {
	
	Matrix normalMatrix;
	
	normalMatrix = getNormalMatrix();
	normalMatrix.toArray(array);
}


Matrix State::getProjectionMatrix() {
	
	GLfloat array[16];
	Matrix matrix;
	
	glGetFloatv(GL_PROJECTION_MATRIX, array);
	matrix.set(array);
	return matrix;
}


void State::pop() {glPopMatrix();}

void State::push() {glPushMatrix();}

void State::setModeAsModelView() {glMatrixMode(GL_MODELVIEW);}

void State::setModeAsProjection() {glMatrixMode(GL_PROJECTION);}

