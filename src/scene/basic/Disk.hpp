/*
 * Disk.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DISK_HPP
#define DISK_HPP
#include "common.h"
#include "Shape.hpp"                    // Base class
#include "Math.hpp"                     // Calculating circle
using namespace std;


/** @brief Circular disk made from a triangle fan.
 * @ingroup basic
 */
class Disk : public Shape {
public:
	Disk(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
};


#endif
