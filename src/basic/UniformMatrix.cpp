/*
 * UniformMatrix.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformMatrix.hpp"


/** @throws NodeException if matrix type not supported. */
UniformMatrix::UniformMatrix(const Tag &tag) : Uniform(tag) {
	
	// Find matrix type
	if (tag.get("as", as, false)) {
		setTypeFromAs();
	} else {
		setTypeFromName();
	}
	
	// Of for light
	tag.get("of", of, false, false);
}


bool UniformMatrix::hasChild(Node *node, const string &name) {
	
	Node::iterator it;
	UniformMatrix *uniform;
	
	for (it=node->begin(); it!=node->end(); ++it) {
		uniform = dynamic_cast<UniformMatrix*>((*it));
		if ((uniform != NULL) && (uniform->getName() == name)) {
			return true;
		}
	}
	return false;
}


bool UniformMatrix::isDefault(const string &name, GLenum type) {
	
	return isMatrixType(type) && isDefaultName(name);
}


/** @return True if @e name matches one of the default matrix names. */
bool UniformMatrix::isDefaultName(const string &name) {
	
	return ((name == DEFAULT_MODELVIEW_MATRIX_NAME)
	        || (name == DEFAULT_PROJECTION_MATRIX_NAME)
	        || (name == DEFAULT_MODELVIEW_PROJECTION_MATRIX_NAME)
	        || (name == DEFAULT_NORMAL_MATRIX_NAME)
	        || (name == DEFAULT_IDENTITY_MATRIX_NAME));
}


/** @throws NodeException if @e as not supported. */
void UniformMatrix::setTypeFromAs() {
	
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


/** @throws NodeException if default name not supported. */
void UniformMatrix::setTypeFromName() {
	
	if (name == DEFAULT_MODELVIEW_PROJECTION_MATRIX_NAME) {
		matrixType = MODELVIEW_PROJECTION;
		as = "modelviewprojection";
	} else if (name == DEFAULT_MODELVIEW_MATRIX_NAME) {
		matrixType = MODELVIEW;
		as = "modelview";
	} else if (name == DEFAULT_NORMAL_MATRIX_NAME) {
		matrixType = NORMAL;
		as = "normal";
	} else if (name == DEFAULT_PROJECTION_MATRIX_NAME) {
		matrixType = PROJECTION;
		as = "projection";
	} else if (name == DEFAULT_IDENTITY_MATRIX_NAME) {
		matrixType = IDENTITY;
		as = "identity";
	} else {
		NodeException e(tag);
		e << "[UniformMatrix] Unrecognized default name and no 'as' attribute.";
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
		State::getModelViewProjectionMatrix(value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	case NORMAL:
		State::getNormalMatrix(value);
		glUniformMatrix3fv(location, 1, false, value);
		break;
	case IDENTITY:
		State::getIdentityMatrix(value);
		glUniformMatrix4fv(location, 1, false, value);
		break;
	}
}


string UniformMatrix::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " as='" << as << "'";
	if (!of.empty())
		stream << " of='" << of << "'";
	return stream.str();
}

