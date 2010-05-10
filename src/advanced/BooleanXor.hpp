/*
 * BooleanXor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEANXOR_HPP
#define BOOLEANXOR_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Boolean.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Exclusive OR boolean operator for two shapes.
 */
class BooleanXor : public Boolean {
public:
	BooleanXor(const Tag &tag) : Boolean(tag,getTraits()) {}
	virtual void associate();
	static ShapeTraits getTraits();
	virtual string toString() const;
protected:
	virtual void calculate();
	pair<Extent,Extent> knife(const Extent &extent, float at, int on);
	virtual void findShapes();
	virtual void findTake();
	virtual void initPoints();
	virtual void initNormals();
	virtual void initCoords() {}
	virtual void updateTangible();
private:
	GLfloat points[72][3];
	int takeID;
	Shape *takeShape;
	list<Extent> pieces;
};


/** Assumed to be always visible (for now). */
inline void BooleanXor::updateTangible() {tangible = true;}


#endif
