/*
 * Numeric.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Numeric.hpp"
double Numeric::PI=355.0/113;


/** Calculates the points in a circle.
 * 
 * @param radius Distance from center to a point
 * @param number Number of points in the circle
 * @return List of points in circle.
 */
list<Vector> Numeric::calculateCircle(float radius, int number) {
	
	double delta, theta, x, y;
	list<Vector> points;
	
	// Initialize
	delta = 360.0 / number;
	
	// Calculate points
	points.push_back(Vector(radius,0,0,1));
	theta = delta;
	while (theta < 360) {
		x = radius * cos(toRadians(theta));
		y = radius * sin(toRadians(theta));
		points.push_back(Vector(x,y,0,1));
		theta += delta;
	}
	
	// Finish
	return points;
}

