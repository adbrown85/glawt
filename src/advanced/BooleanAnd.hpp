/*
 * BooleanAnd.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEANAND_HPP
#define BOOLEANAND_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Boolean.hpp"
using namespace std;


class BooleanAnd : public Boolean {
public:
	BooleanAnd(const Tag &tag);
	virtual void draw() const;
	virtual void initIndices();
	virtual void initPoints();
	virtual void updateCoords();
	virtual void updatePoints();
	virtual void updateTangible();
private:
	GLfloat points[8][3], coords0[8][3], coords1[8][3];
	GLshort indices[24];
};


#endif
