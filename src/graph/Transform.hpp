/*
 * Transform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Matrix.hpp"
using namespace std;


class Transform {
	
	public :
		
		static Matrix getModelViewMatrix();
		static Matrix getModelViewProjectionMatrix();
		static void getModelViewProjectionMatrix(GLfloat array[16]);
		static Matrix getNormalMatrix();
		static void getNormalMatrix(GLfloat array[9]);
		static Matrix getProjectionMatrix();
};


#endif
