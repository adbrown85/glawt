/*
 * BooleanAnd.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanAnd.hpp"


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
	
	Coordinates C;
	map<Shape*,Extent>::iterator ei;
	map<int,Coordinates>::iterator ui;
	UniformSampler *sampler;
	
	// Calculate coordinates from overlap
	for (ei=extents.begin(); ei!=extents.end(); ++ei) {
		C.upper = (overlap.upper - ei->second.lower) / ei->second.diagonal;
		C.upper.z = 1.0 - C.upper.z;
		C.lower = (overlap.lower - ei->second.lower) / ei->second.diagonal;
		C.lower.z = 1.0 - C.lower.z;
		sampler = findSampler(ei->first);
		units[sampler->getValue()] = C;
	}
	
	// Update coords in buffer
	int i=0;
	for (ui=units.begin(); ui!=units.end(); ++ui) {
		toArray(coords[i], ui->second.lower, ui->second.upper);
		++i;
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

