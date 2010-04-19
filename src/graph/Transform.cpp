/*
 * Transform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transform.hpp"


Matrix Transform::getModelViewMatrix() {
	
	GLfloat array[16];
	Matrix matrix;
	
	glGetFloatv(GL_MODELVIEW_MATRIX, array);
	matrix.set(array);
	return matrix;
}


Matrix Transform::getProjectionMatrix() {
	
	GLfloat array[16];
	Matrix matrix;
	
	glGetFloatv(GL_PROJECTION_MATRIX, array);
	matrix.set(array);
	return matrix;
}


Matrix Transform::getModelViewProjectionMatrix() {
	
	Matrix mvMatrix, pMatrix;
	
	mvMatrix = getModelViewMatrix();
	pMatrix = getProjectionMatrix();
	return pMatrix * mvMatrix;
}


void Transform::getModelViewProjectionMatrix(GLfloat array[16]) {
	
	Matrix mvpMatrix;
	
	mvpMatrix = getModelViewProjectionMatrix();
	mvpMatrix.toArray(array);
}

