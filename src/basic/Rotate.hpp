/*
 * Rotate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ROTATE_HPP
#define ROTATE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Node that reorients items in the scene.
 */
class Rotate : public Transformation {
public:
	Rotate(const Tag &tag);
	virtual void apply();
	virtual void remove();
	virtual string toString() const;
private:
	float angle;
	Vector axis;
};


#endif
