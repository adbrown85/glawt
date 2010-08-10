/*
 * State.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef STATE_HPP
#define STATE_HPP
#include "common.h"
#include <stack>
#include "Matrix.hpp"
using namespace std;


/* Enumeration for keeping track of mode. */
enum MatrixMode {MODEL_MODE, VIEW_MODE, PROJECTION_MODE};

/** @brief Utility for manipulating the transformation stack.
 * @ingroup scene
 */
class State {
public: // Mutators
	static void apply(const Matrix &matrix);
	static void loadIdentity();
	static void pop();
	static void push();
	static void setMode(MatrixMode mode);
public: // Accessors
	static Matrix getIdentityMatrix();
	static void getIdentityMatrix(GLfloat array[16]);
	static Matrix getModelMatrix();
	static void getModelMatrix(GLfloat array[16]);
	static Matrix getModelViewMatrix();
	static void getModelViewMatrix(GLfloat array[16]);
	static Matrix getModelViewProjectionMatrix();
	static void getModelViewProjectionMatrix(GLfloat array[16]);
	static Matrix getNormalMatrix();
	static void getNormalMatrix(GLfloat array[9]);
	static Matrix getProjectionMatrix();
	static void getProjectionMatrix(GLfloat array[16]);
	static Matrix getViewMatrix();
	static void getViewMatrix(GLfloat array[16]);
private:
	static GLuint mode;
	static stack<Matrix> mStack;
	static stack<Matrix> vStack;
	static stack<Matrix> pStack;
};


#endif
