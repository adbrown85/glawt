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
	A =    extents.begin() ->second;
	B = (++extents.begin())->second;
	if (A.label != takeID) {
		swap(A, B);
	}
	
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


void BooleanXor::findShapes() {
	
	Boolean::findShapes();
	
	// Check size
	if (shapes.size() != 2) {
		NodeException e(tag);
		e << "[BooleanXor] Must use two shapes.";
		throw e;
	}
}


/** Searches for the shape the operation should limit its output to.
 * 
 * @throws NodeException if a shape matching @e only cannot be found.
 */
void BooleanXor::findTake() {
	
	string text;
	list<Shape*>::iterator it;
	Shape *shape;
	
	// Look through list of shapes for matching name
	tag.get("take", text, true, false);
	takeShape = NULL;
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		shape = *it;
		if (shape->getName() == text) {
			takeID = shape->getID();
			takeShape = shape;
		}
	}
	
	// Make sure it found it
	if (takeShape == NULL) {
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
	
	if (isOverlapped()) {
		calculate();
		count = 0;
		list<Extent>::iterator it;
		for (it=pieces.begin(); it!=pieces.end(); ++it) {
			toArray(points+count, it->lower, it->upper);
			count += 24;
		}
	} else {
		map<Shape*,Extent>::iterator it;
		it = extents.find(takeShape);
		toArray(points   , it->second.lower, it->second.upper);
		count = 24;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}


void BooleanXor::initNormals() {
	
	GLfloat normals[72][3];
	
	toNormals(normals);
	toNormals(normals+24);
	toNormals(normals+48);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(1), sizeof(normals), normals);
}


void BooleanXor::initCoords() {
	
	Extent extent;
	int off;
	list<Extent>::iterator it;
	Coordinates C;
	
	// Calculate each piece based on overlap
	if (isOverlapped()) {
		extent = extents.find(takeShape)->second;
		off = 0;
		for (it=pieces.begin(); it!=pieces.end(); ++it) {
			C.upper = (it->upper - extent.lower) / extent.diagonal;
			C.upper.z = 1.0 - C.upper.z;
			C.lower = (it->lower - extent.lower) / extent.diagonal;
			C.lower.z = 1.0 - C.lower.z;
			toArray(coords+off, C.lower, C.upper);
			off += 24;
		}
	}
	
	// Or if not overlapped just send regular coordinates
	else {
		toArray(coords, Vector(0,0,1), Vector(1,1,0));
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords), coords);
}


pair<Extent,Extent> BooleanXor::knife(const Extent &extent, float at, int on) {
	
	Extent l, u;
	
	l = extent;
	l.upper[on] = at;
	l.diagonal = l.upper - l.lower;
	u = extent;
	u.lower[on] = at;
	u.diagonal = u.upper - u.lower;
	return pair<Extent,Extent>(l,u);
}


string BooleanXor::toString() const {
	
	ostringstream stream;
	
	stream << Boolean::toString();
	stream << " take='" << takeShape->getName() << "'";
	return stream.str();
}

