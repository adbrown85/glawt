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
	findUniforms();
}


/** Checks that the shape formed by the operation can be shown. */
void BooleanAnd::calculateTangible() {
	
	tangible = isOverlapped();
}


/** Finds and copies uniforms from each shape. */
void BooleanAnd::findUniforms() {
	
	Node *node;
	Uniform *uniform;
	ostringstream stream;
	Tag tag;
	
	// For each child under each shape
	for (size_t i=0; i<shapes.size(); ++i) {
		Node::iterator it;
		for (it=shapes[i]->begin(); it!=shapes[i]->end(); ++it) {
			
			// See if it's a uniform
			uniform = dynamic_cast<Uniform*>(*it);
			if (uniform == NULL) {
				continue;
			}
			
			// If so, copy it
			tag = uniform->getTag();
			tag.setLine(this->tag.getLine());
			stream.str("");
			stream << tag["name"] << i;
			tag["name"] = stream.str();
			node = Factory::create(tag);
			addChild(node);
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
void BooleanAnd::updateBufferPoints() {
	
	// Update points from overlap
	toArray(points, overlap.lower, overlap.upper);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
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
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords[0]), coords[0]);
	glBufferSubData(GL_ARRAY_BUFFER, offset(3), sizeof(coords[1]), coords[1]);
}

