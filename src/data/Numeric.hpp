/*
 * Numeric.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NUMERIC_HPP
#define NUMERIC_HPP
#include "common.h"
#include <cmath>                        // sin, cos
#include <list>                         // Storing points
#include "Vector.hpp"                   // Storing points
using namespace std;


/**
 * @ingroup data
 * @brief Math-related utilities.
 */
class Numeric {
public:
	static list<Vector> calculateCircle(float radius, int number);
	static double toRadians(double degrees);
public:
	static double PI;
};

/** Converts degrees to radians. */
inline double Numeric::toRadians(double deg) {return deg * Numeric::PI / 180;}


#endif
