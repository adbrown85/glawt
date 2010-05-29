/*
 * Line.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LINE_HPP
#define LINE_HPP
#include "common.h"
#include "Shape.hpp"                    // Base class
using namespace std;


/** @brief %Line between two points.
 * @ingroup basic
 */
class Line : public Shape {
public:
	Line(const Tag &tag);
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
private:
	float from[4], to[4];
};


#endif
