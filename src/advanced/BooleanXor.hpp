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


typedef list<Extent> extent_list;


/**
 * @ingroup advanced
 * @brief Exclusive OR boolean operator for two shapes.
 */
class BooleanXor : public Boolean {
public:
	BooleanXor(const Tag &tag) : Boolean(tag,getTraits()) {}
	static ShapeTraits getTraits();
protected:
	virtual void calculate();
	virtual void calculate(Extent A, Extent B);
	pair<Extent,Extent> knife(Extent &extent, float at, int on);
	virtual void initPoints();
	virtual void initNormals() {}
	virtual void initCoords() {}
	virtual void updateTangible();
private:
	//GLint uses[2];
	//GLfloat piece[2][3][24][3];
	GLfloat points[72][3];
	map<int,extent_list> pieces;
};


/** Assumed to be always visible (for now). */
inline void BooleanXor::updateTangible() {tangible = true;}


#endif
