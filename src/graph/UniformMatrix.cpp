/*
 * UniformMatrix.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformMatrix.hpp"


UniformMatrix::UniformMatrix(const Tag &tag) :
                             Uniform(tag) {
	
	// Basices
	className = "UniformMatrix";
	
	// Find link
	if (link == "modelview") {
		matrixType = MODELVIEW;
	} else if (link == "projection") {
		matrixType = PROJECTION;
	} else if (link == "modelviewprojection") {
		matrixType = MODELVIEW_PROJECTION;
	} else {
		throw "[UniformMatrix] Matrix not supported.";
	}
}


void UniformMatrix::apply() {
	
	switch (matrixType) {
	case MODELVIEW:
		glGetFloatv(GL_MODELVIEW_MATRIX, value);
		break;
	case PROJECTION:
		glGetFloatv(GL_PROJECTION_MATRIX, value);
		break;
	case MODELVIEW_PROJECTION:
		Transform::getModelViewProjectionMatrix(value);
		break;
	}
	glUniformMatrix4fv(location, 1, false, value);
}


void UniformMatrix::remove() {
	
	
}

