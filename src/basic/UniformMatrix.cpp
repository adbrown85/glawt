/*
 * UniformMatrix.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformMatrix.hpp"


UniformMatrix::UniformMatrix(const Tag &tag) :
                             Uniform("UniformMatrix", tag) {
	
	// Find link
	if (link == "modelview") {
		matrixType = MODELVIEW;
	} else if (link == "projection") {
		matrixType = PROJECTION;
	} else if (link == "modelviewprojection") {
		matrixType = MODELVIEW_PROJECTION;
	} else if (link == "normal") {
		matrixType = NORMAL;
	} else {
		throw "[UniformMatrix] Matrix not supported.";
	}
}


void UniformMatrix::apply() {
	
	switch (matrixType) {
	case MODELVIEW:
		glGetFloatv(GL_MODELVIEW_MATRIX, value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	case PROJECTION:
		glGetFloatv(GL_PROJECTION_MATRIX, value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	case MODELVIEW_PROJECTION:
		Transform::getModelViewProjectionMatrix(value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	case NORMAL:
		Transform::getNormalMatrix(value);
		glUniformMatrix3fv(location, 1, false, value);
		break;
	}
}

