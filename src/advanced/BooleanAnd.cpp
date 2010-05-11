/*
 * BooleanAnd.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanAnd.hpp"


/** Finds required connections to other nodes. */
void BooleanAnd::associate() {
	
	Boolean::associate();
	findUnits();
}


/** Find sampler that a shape uses. */
UniformSampler* BooleanAnd::findSampler(Shape *shape) {
	
	Node::iterator it;
	UniformSampler *sampler;
	
	// Check each child for a sampler
	for (it=shape->begin(); it!=shape->end(); ++it) {
		sampler = dynamic_cast<UniformSampler*>(*it);
		if (sampler != NULL)
			return sampler;
	}
	return NULL;
}


/** Finds the texture units for each shape. */
void BooleanAnd::findUnits() {
	
	vector<Shape*>::iterator it;
	UniformSampler *sampler;
	
	// Store unit from sampler under each shape
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		sampler = findSampler(*it);
		if (sampler == NULL) {
			units.push_back(-1);
		} else {
			units.push_back(sampler->getValue());
		}
	}
}


/** @return parameters to use for the shape. */
ShapeTraits BooleanAnd::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 24;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.addAttribute("MCVertex");
	traits.addAttribute("MCNormal");
	traits.addAttribute("TexCoord0");
	traits.addAttribute("TexCoord1");
	return traits;
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
void BooleanAnd::initPoints() {
	
	// Update points from overlap
	toArray(points, overlap.lower, overlap.upper);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}


/** Updates the texture coordinates in the vertex buffer. */
void BooleanAnd::initCoords() {
	
	Extent C;
	list<Extent>::iterator it;
	
	// Calculate coordinates from overlap
	for (size_t i=0; i<extents.size(); ++i) {
		C.upper = (overlap.upper - extents[i].lower) / extents[i].diagonal;
		C.upper.z = 1.0 - C.upper.z;
		C.lower = (overlap.lower - extents[i].lower) / extents[i].diagonal;
		C.lower.z = 1.0 - C.lower.z;
		toArray(coords[i], C.lower, C.upper);
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords[0]), coords[0]);
	glBufferSubData(GL_ARRAY_BUFFER, offset(3), sizeof(coords[1]), coords[1]);
}


/** Checks that the shape formed by the operation can be shown. */
void BooleanAnd::updateTangible() {
	
	tangible = isOverlapped();
}

