/*
 * Math.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MATH_HPP
#define MATH_HPP
#include "common.h"
#include <cmath>                        // sin, cos
#include "Vector.hpp"                   // Storing points
using namespace std;


/** @brief Math-related utilities.
 * @ingroup system
 */
class Math {
public:
	static list<Vector> computeCircle(float radius, int number);
	static double toRadians(double degrees);
public:
	static double PI;
};

/** Converts degrees to radians. */
inline double Math::toRadians(double deg) {return deg * Math::PI / 180;}


#endif
