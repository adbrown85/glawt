/*
 * BooleanXor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanXor.hpp"


void BooleanXor::associate() {
	
	Boolean::associate();
	findTake();
}


void BooleanXor::calculate() {
	
	Extent A, B;
	pair<Extent,Extent> result;
	
	// Initialize
	pieces.clear();
	A = extents[ take];
	B = extents[!take];
	
	// Split
	for (int i=0; i<3; ++i) {
		if (A.lower[i] < B.lower[i]) {
			if (A.upper[i] > B.lower[i]) {
				result = knife(A, B.lower[i], i);
				if (isSubstantial(result.first)) {
					pieces.push_back(result.first);
					A = result.second;
				}
			}
		} else {
			if (B.lower[i] < A.lower[i]) {
				result = knife(A, B.upper[i], i);
				if (isSubstantial(result.second)) {
					pieces.push_back(result.second);
					A = result.first;
				}
			}
		}
	}
}


/** Searches for the shape the operation should limit its output to.
 * 
 * @throws NodeException if a shape matching @e only cannot be found.
 */
void BooleanXor::findTake() {
	
	string text;
	
	// Get name of shape
	tag.get("take", text, true, false);
	
	// Look through list of shapes for it
	take = UINT_MAX;
	for (size_t i=0; i<shapes.size(); ++i) {
		if (shapes[i]->getName() == text) {
			take = i;
			break;
		}
	}
	
	// Make sure it was found
	if (take == UINT_MAX) {
		NodeException e(tag);
		e << "[BooleanXor] Could not find shape named '" << text << "'.";
		throw e;
	}
}


ShapeTraits BooleanXor::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 72;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	return traits;
}


void BooleanXor::initPoints() {
	
	list<Extent>::iterator it;
	
	// Overlapped so form points from pieces
	if (isOverlapped()) {
		calculate();
		count = 0;
		for (it=pieces.begin(); it!=pieces.end(); ++it) {
			toArray(points+count, it->lower, it->upper);
			count += 24;
		}
	}
	
	// Otherwise send just the shape itself
	else {
		toArray(points, extents[take].lower, extents[take].upper);
		count = 24;
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}


void BooleanXor::initNormals() {
	
	GLfloat normals[72][3];
	
	// Fill array with normals
	toNormals(normals);
	toNormals(normals+24);
	toNormals(normals+48);
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(1), sizeof(normals), normals);
}


void BooleanXor::initCoords() {
	
	int off;
	list<Extent>::iterator it;
	Vector lower(0,0,1), upper(1,1,0);
	
	// Calculate coordinates of each piece based on extent of total shape
	if (isOverlapped()) {
		off = 0;
		for (it=pieces.begin(); it!=pieces.end(); ++it) {
			upper = (it->upper - extents[take].lower) / extents[take].diagonal;
			upper.z = 1.0 - upper.z;
			lower = (it->lower - extents[take].lower) / extents[take].diagonal;
			lower.z = 1.0 - lower.z;
			toArray(coords+off, lower, upper);
			off += 24;
		}
	}
	
	// Or if not overlapped just send regular coordinates
	else {
		toArray(coords, lower, upper);
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords), coords);
}


pair<Extent,Extent> BooleanXor::knife(const Extent &extent, float at, int on) {
	
	Extent l, u;
	
	// Lower section
	l = extent;
	l.upper[on] = at;
	l.diagonal = l.upper - l.lower;
	
	// Upper section
	u = extent;
	u.lower[on] = at;
	u.diagonal = u.upper - u.lower;
	
	// Finish
	return pair<Extent,Extent>(l,u);
}


string BooleanXor::toString() const {
	
	ostringstream stream;
	
	stream << Boolean::toString();
	stream << " take='" << take << "'";
	return stream.str();
}

