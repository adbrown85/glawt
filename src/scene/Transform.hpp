/*
 * Transform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "common.h"
#include "Matrix.hpp"
using namespace std;


/** @brief Utility for manipulating the transformation stack.
 * @ingroup scene
 */
class Transform {
public:
	static void getIdentityMatrix(GLfloat array[16]);
	static Matrix getModelViewMatrix();
	static Matrix getModelViewProjectionMatrix();
	static void getModelViewProjectionMatrix(GLfloat array[16]);
	static Matrix getNormalMatrix();
	static void getNormalMatrix(GLfloat array[9]);
	static Matrix getProjectionMatrix();
};


#endif
