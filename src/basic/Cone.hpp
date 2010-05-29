/*
 * Cone.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CONE_HPP
#define CONE_HPP
#include "common.h"
#include "Shape.hpp"                    // Base class
#include "Math.hpp"                     // Calculating circle
using namespace std;


/** @brief Cone made from triangles.
 * @ingroup basic
 */
class Cone : public Shape {
public:
	Cone(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
};


#endif
