/*
 * UniformMatrix.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformMatrix.hpp"


/**
 * @throws NodeException if matrix type not supported.
 */
UniformMatrix::UniformMatrix(const Tag &tag) :
                             Uniform(tag) {
	
	// Find link
	tag.get("as", as);
	if (as == "modelview") {
		matrixType = MODELVIEW;
	} else if (as == "projection") {
		matrixType = PROJECTION;
	} else if (as == "modelviewprojection") {
		matrixType = MODELVIEW_PROJECTION;
	} else if (as == "normal") {
		matrixType = NORMAL;
	} else if (as == "identity") {
		matrixType = IDENTITY;
	} else {
		NodeException e(tag);
		e << "[UniformMatrix] Matrix '" << as << "' not supported.";
		throw e;
	}
}


void UniformMatrix::apply() {
	
	if (location == -1)
		return;
	
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
	case IDENTITY:
		Transform::getIdentityMatrix(value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	}
}


string UniformMatrix::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " as='" << as << "'";
	return stream.str();
}

