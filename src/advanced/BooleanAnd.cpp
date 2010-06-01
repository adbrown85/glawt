/*
 * BooleanAnd.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanAnd.hpp"


/** Calls base then renames the uniforms. */
void BooleanAnd::associate() {
	
	Boolean::associate();
	renameUniforms();
}


/** Checks that the shape formed by the operation can be shown. */
void BooleanAnd::calculateTangible() {
	
	tangible = isOverlapped();
}


/** Applies all the copied uniforms, then calls base. */
void BooleanAnd::draw() const {
	
	applyUniforms();
	Boolean::draw();
}


/** @return parameters to use for the shape. */
ShapeTraits BooleanAnd::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 24;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	traits.attributes.push_back("TexCoord1");
	return traits;
}


/** Appends index number to each uniform so they can be used simultaneously. */
void BooleanAnd::renameUniforms() {
	
	list<Uniform*>::iterator it;
	ostringstream stream;
	Tag tag;
	
	// Append index number to each uniform
	for (int i=0; i<2; ++i) {
		for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
			stream.str();
			stream << getName() << i;
			(*it)->setName(stream.str());
		}
	}
}


/** Updates the points in the vertex buffer.
 * 
 * <pre>
 *     6-------7
 *    /|      /|
 *   2-------3 |
 *   | 4-----|-5
 *   |/      |/
 *   0-------1
 * </pre>
 */
void BooleanAnd::updateBufferPoints() {
	
	// Update points from overlap
	toArray(points, overlap.lower, overlap.upper);
	setBufferData("MCVertex", points);
}


/** Updates the texture coordinates in the vertex buffer. */
void BooleanAnd::updateBufferCoords() {
	
	Vector upper, lower;
	list<Extent>::iterator it;
	
	// Calculate coordinates from overlap
	for (size_t i=0; i<extents.size(); ++i) {
		upper = (overlap.upper - extents[i].lower) / extents[i].diagonal;
		upper.z = 1.0 - upper.z;
		lower = (overlap.lower - extents[i].lower) / extents[i].diagonal;
		lower.z = 1.0 - lower.z;
		toArray(coords[i], lower, upper);
	}
	
	// Send to buffer
	setBufferData("TexCoord0", coords[0]);
	setBufferData("TexCoord1", coords[1]);
}

