/*
 * Disk.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DISK_HPP
#define DISK_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Shape.hpp"                    // Base class
#include "Numeric.hpp"                  // Calculating circle
using namespace std;


/**
 * @ingroup basic
 * @brief Circular disk made from a triangle fan.
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
