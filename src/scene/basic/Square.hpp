/*
 * Square.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "common.h"
#include "Shape.hpp"                    // Base class
using namespace std;


/** @brief Four-sided, 2D shape with equal width and height.
 * @ingroup basic
 */
class Square : public Shape {
public:
	Square(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
	virtual void updateBufferCoords();
};


#endif
