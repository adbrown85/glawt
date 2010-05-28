/*
 * BooleanXor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEANXOR_HPP
#define BOOLEANXOR_HPP
#include "common.h"
#include <algorithm>
#include <climits>
#include "Boolean.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Exclusive OR boolean operator for two shapes.
 * 
 * Uses the following vertex attributes:
 *   - MCVertex
 *   - MCNormal
 *   - TexCoord0
 */
class BooleanXor : public Boolean {
public:
	BooleanXor(const Tag &tag) : Boolean(tag,getTraits()) {}
	virtual void associate();
	static ShapeTraits getTraits();
	virtual string toString() const;
protected:
	virtual void calculate();
	virtual void calculateTangible();
	virtual void findTake();
	pair<Extent,Extent> knife(const Extent &extent, float at, int on);
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
	virtual void updateBufferCoords();
private:
	GLfloat points[72][3], coords[72][3];
	GLuint take;
	list<Extent> pieces;
};


/** Assumed to be always visible (for now). */
inline void BooleanXor::calculateTangible() {tangible = true;}


#endif
