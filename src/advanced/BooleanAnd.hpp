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


/**
 * @ingroup advanced
 * @brief Boolean AND operation of two shapes.
 */
class BooleanAnd : public Boolean {
public:
	BooleanAnd(const Tag &tag) : Boolean(tag,getTraits()) {};
	static ShapeTraits getTraits();
	virtual void initPoints();
	virtual void initCoords();
	virtual bool isTangible();
private:
	GLfloat points[24][3], coords[2][24][3];
};


#endif
