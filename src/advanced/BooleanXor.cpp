/*
 * BooleanXor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanXor.hpp"


/** Sets the @e only attribute. */
BooleanXor::BooleanXor(const Tag &tag) : Boolean(tag,getTraits()) {
	
	string only;
	
	// Only
	tag.get("only", only, false, true);
	if (only.empty()) {
		this->only = ALL;
	} else if (only == "behind") {
		this->only = BEHIND;
	} else if (only == "forward") {
		this->only = FORWARD;
	} else if (only == "beside") {
		this->only = BESIDE;
	} else {
		NodeException e(tag);
		e << "[BooleanXOR] 'only' must be 'behind', 'forward', or 'beside'.";
		throw e;
	}
}


/** Creates the pieces by knifing at the intersection point of each axis. */
void BooleanXor::calculate() {
	
	Extent A, B;
	
	// Explode the two pieces
	pieces.clear();
	A = extents[0];
	B = extents[1];
	explode(A, 0, pieces);
	explode(B, 0, pieces);
}


/** Draw the pieces or one of the shapes according to overlap and depth. */
void BooleanXor::draw() const {
	
	Matrix rotation;
	
	// Get rotation from the canvas
	rotation = getCanvas()->getCamera()->getRotation();
	
	// Draw depending on overlap
	if (isOverlapped()) {
		drawWhenOverlapped(rotation);
	} else {
		drawWhenNotOverlapped(rotation);
	}
}


/** Draws one of the shapes according to depth. */
void BooleanXor::drawWhenNotOverlapped(Matrix &rotation) const {
	
	float depths[2];
	int i;
	vector<Extent>::const_iterator it;
	
	// Find which shape is farthest back
	for (it=extents.begin(); it!=extents.end(); ++it) {
		i = distance(extents.begin(), it);
		depths[i] = (rotation * ((it->upper+it->lower)*0.5)).z;
	}
	i = (depths[1] < depths[0]) ? 1 : 0;
	
	// Only draw that one
	Shape::draw(i*24, 24);
}


/** Draw some of the pieces according to depth. */
void BooleanXor::drawWhenOverlapped(Matrix &rotation) const {
	
	float oDepth, pDepth;
	int offset;
	list<Extent>::const_iterator li;
	multimap<float,int> sorted;
	multimap<float,int>::iterator mi;
	
	// Calculate depth of overlap
	oDepth = (rotation * ((overlap.upper+overlap.lower)*0.5)).z; 
	
	// Calculate depths of pieces and sort using map if behind overlap
	for (li=pieces.begin(); li!=pieces.end(); ++li) {
		pDepth = (rotation * ((li->upper+li->lower)*0.5)).z;
		if (pDepth < oDepth) {
			offset = distance(pieces.begin(),li) * 24;
			sorted.insert(pair<float,int>(pDepth, offset));
		}
	}
	
	// Draw the pieces
	for (mi=sorted.begin(); mi!=sorted.end(); ++mi) {
		Shape::draw(mi->second, 24);
	}
}


/** Adds @e piece to @e pieces only if it's substantial. */
void BooleanXor::addPiece(list<Extent> &pieces, const Extent &piece) {
	
	if (isSubstantial(piece)) {
		pieces.push_back(piece);
	}
}


/** Recursively splits a piece. */
void BooleanXor::explode(const Extent &piece, int d, list<Extent> &pieces) {
	
	bool low;
	pair<Extent,Extent> result;
	
	// Knife the piece
	low = ((overlap.lower[d] - piece.lower[d]) > 0.0001);
	if (low) {
		result = knife(piece, overlap.lower[d], d);
	} else {
		result = knife(piece, overlap.upper[d], d);
	}
	
	// Z direction ends it
	if (d == 2) {
		if (fabs(piece.lower.x - overlap.lower.x) < 0.0001
		      && fabs(piece.lower.y - overlap.lower.y) < 0.0001) {
			addPiece(pieces, low ? result.first : result.second);
		} else {
			addPiece(pieces, result.first);
			addPiece(pieces, result.second);
		}
		return;
	}
	
	// Recurse on X and Y directions
	explode(result.first, d+1, pieces);
	explode(result.second, d+1, pieces);
}


ShapeTraits BooleanXor::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = BOOLEAN_XOR_COUNT;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	return traits;
}


/** @return Two pieces of @e extent cut at @e at along the @e on axis. */
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
	string only;
	
	stream << Boolean::toString();
	tag.get("only", only, false, true);
	if (!only.empty()) {
		stream << " only='" << only << "'";
	}
	return stream.str();
}


void BooleanXor::updateBufferPoints() {
	
	int tally;
	list<Extent>::iterator it;
	
	// Overlapped so form points from pieces
	if (isOverlapped()) {
		calculate();
		tally = 0;
		for (it=pieces.begin(); it!=pieces.end(); ++it) {
			toArray(points+tally, it->lower, it->upper);
			tally += 24;
		}
		setCount(tally);
	}
	
	// Otherwise send just the shapes themselves
	else {
		toArray(points+ 0, extents[0].lower, extents[0].upper);
		toArray(points+24, extents[1].lower, extents[1].upper);
		setCount(48);
	}
	
	// Send to buffer
	setBufferData("MCVertex", points);
}


void BooleanXor::updateBufferNormals() {
	
	int i;
	GLfloat normals[BOOLEAN_XOR_COUNT][3];
	
	// Fill array with normals
	for (int i=0; i<BOOLEAN_XOR_COUNT; i+=24) {
		toNormals(normals+i);
	}
	
	// Send to buffer
	setBufferData("MCNormal", normals);
}


void BooleanXor::updateBufferCoords() {
	
	int index, offset;
	list<Extent>::iterator p;
	Vector lower(0,0,1), upper(1,1,0);
	
	// Calculate coordinates of each piece based on extent of total shape
	if (isOverlapped()) {
		offset = 0;
		for (p=pieces.begin(); p!=pieces.end(); ++p) {
			index = p->index;
			upper = (p->upper - extents[index].lower) / extents[index].diagonal;
			upper.z = 1.0 - upper.z;
			lower = (p->lower - extents[index].lower) / extents[index].diagonal;
			lower.z = 1.0 - lower.z;
			toArray(coords+offset, lower, upper);
			offset += 24;
		}
	}
	
	// Or if not overlapped just send regular coordinates
	else {
		toArray(coords+ 0, lower, upper);
		toArray(coords+24, lower, upper);
	}
	
	// Send to buffer
	setBufferData("TexCoord0", coords);
}

