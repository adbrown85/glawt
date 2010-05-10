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
	
	Extent *l, *h;
	pair<Extent,Extent> result;
	
	// Initialize
	pieces.clear();
	l = &(   extents.begin() ->second);
	h = &((++extents.begin())->second);
	
	// Split
	for (int i=0; i<3; ++i) {
		if (l->lower[i] > h->lower[i]) {
			swap(l, h);
		}
		if (h->lower[i] < l->upper[i]) {
			result = knife(*l, h->lower[i], i);
			if (l->label == takeID)
				pieces.push_back(result.first);
			*l = result.second;
			result = knife(*h, l->upper[i], i);
			if (h->label == takeID)
				pieces.push_back(result.second);
			*h = result.first;
		}
	}
	
	// Filter out bad pieces
	list<Extent>::iterator it;
	for (it=pieces.begin(); it!=pieces.end(); ++it) {
		it->diagonal = it->upper - it->lower;
		for (int i=0; i<3; ++i) {
			if (fabs(it->diagonal[i]) < 0.05) {
				it = pieces.erase(it);
				break;
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


pair<Extent,Extent> BooleanXor::knife(Extent &extent, float at, int on) {
	
	pair<Extent,Extent> result;
	
	result.first = extent;
	result.first.upper[on] = at;
	result.second = extent;
	result.second.lower[on] = at;
	return result;
}


ShapeTraits BooleanXor::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 72;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
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


string BooleanXor::toString() const {
	
	ostringstream stream;
	
	stream << Boolean::toString();
	stream << " take='" << takeShape->getName() << "'";
	return stream.str();
}

