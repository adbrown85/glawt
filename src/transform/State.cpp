/*
 * State.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "State.hpp"
GLuint State::mode=MODEL_MODE;
MatrixStack State::mStack, State::vStack, State::pStack;


void State::apply(const Matrix &matrix) {
	
	switch (mode) {
	case MODEL_MODE:
		mStack.top() = mStack.top() * matrix;
		break;
	case VIEW_MODE:
		vStack.top() = vStack.top() * matrix;
		break;
	case PROJECTION_MODE:
		pStack.top() = pStack.top() * matrix;
		break;
	}
}


void State::loadIdentity() {
	
	switch (mode) {
	case MODEL_MODE:
		mStack.top() = Matrix();
		break;
	case VIEW_MODE:
		vStack.top() = Matrix();
		break;
	case PROJECTION_MODE:
		pStack.top() = Matrix();
		break;
	}
}


void State::push() {
	
	switch (mode) {
	case MODEL_MODE:
		mStack.push();
		break;
	case VIEW_MODE:
		vStack.push();
		break;
	case PROJECTION_MODE:
		pStack.push();
		break;
	}
}


void State::pop() {
	
	switch (mode) {
	case MODEL_MODE:
		mStack.pop();
		break;
	case VIEW_MODE:
		vStack.pop();
		break;
	case PROJECTION_MODE:
		pStack.pop();
		break;
	}
}


Matrix State::getIdentityMatrix() {
	
	return Matrix();
}


void State::getIdentityMatrix(GLfloat array[16]) {
	
	getIdentityMatrix().toArray(array);
}


Matrix State::getModelMatrix() {
	
	return mStack.top();
}


void State::getModelMatrix(GLfloat array[16]) {
	
	return getModelMatrix().toArray(array);
}


Matrix State::getModelViewMatrix() {
	
	return vStack.top() * mStack.top();
}


void State::getModelViewMatrix(GLfloat array[16]) {
	
	return getModelViewMatrix().toArray(array);
}


Matrix State::getModelViewProjectionMatrix() {
	
	return pStack.top() * vStack.top() * mStack.top();
}


void State::getModelViewProjectionMatrix(GLfloat array[16]) {
	
	getModelViewProjectionMatrix().toArray(array);
}


Matrix State::getNormalMatrix() {
	
	return getModelViewMatrix().getInverse().getTranspose();
}


void State::getNormalMatrix(GLfloat array[9]) {
	
	getNormalMatrix().toArray(array);
}


Matrix State::getProjectionMatrix() {
	
	return pStack.top();
}


void State::getProjectionMatrix(GLfloat array[16]) {
	
	return getProjectionMatrix().toArray(array);
}


Matrix State::getViewMatrix() {
	
	return vStack.top();
}


void State::getViewMatrix(GLfloat array[16]) {
	
	return getViewMatrix().toArray(array);
}


void State::setMode(MatrixMode mode) {
	
	State::mode = mode;
}

