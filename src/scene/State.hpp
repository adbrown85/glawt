/*
 * State.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef STATE_HPP
#define STATE_HPP
#include "common.h"
#include "Matrix.hpp"
using namespace std;


/** @brief Utility for manipulating the transformation stack.
 * @ingroup scene
 */
class State {
public:
	static void apply(Matrix &matrix);
	static void getIdentityMatrix(GLfloat array[16]);
	static Matrix getModelViewMatrix();
	static Matrix getModelViewProjectionMatrix();
	static void getModelViewProjectionMatrix(GLfloat array[16]);
	static Matrix getNormalMatrix();
	static void getNormalMatrix(GLfloat array[9]);
	static Matrix getProjectionMatrix();
	static void pop();
	static void push();
	static void setModeAsModelView();
	static void setModeAsProjection();
};


#endif
