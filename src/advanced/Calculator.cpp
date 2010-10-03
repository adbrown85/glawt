/*
 * Calculator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Calculator.hpp"


/** Initializes attributes. */
Calculator::Calculator(set<Shape*> shapes) {
	
	this->shapes = shapes;
	this->canvas = NULL;
}


/** @throw Exception if canvas has not been set. */
void Calculator::checkCanvas() {
	
	if (canvas == NULL) {
		throw Exception("[Calculator] Calculation requires canvas.");
	}
}


GLint Calculator::getCalculationFor(const string &name) {
	
	if (name == "zdistribution") {
		return Calculation::DISTRIBUTION_Z;
	} else {
		return Calculation::NONE;
	}
}


/** Performs a calculation based on an enumeration.
 * 
 * @throw Exception if calculation not supported.
 */
void Calculator::run(GLint calculation, GLsizei count, float *values) {
	
	switch (calculation) {
	case Calculation::DISTRIBUTION_Z:
		runDistributionZ(count, values);
		break;
	default:
		throw Exception("[Calculator] Calculation not supported.");
	}
}


/** Calculates series of steps from the minimum to maximum depth in the scene.
 * 
 * @throw Exception from checkCanvas()
 */
void Calculator::runDistributionZ(GLsizei count, float *values) {
	
	float depth, increment;
	float minimum=+FLT_MAX, maximum=-FLT_MAX;
	Matrix view;
	set<Shape*>::iterator it;
	
	// Get view matrix
	checkCanvas();
	view = canvas->getCamera()->getViewMatrix();
	
	// Find minimum and maximum
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		depth = (view * (*it)->getPosition()).z;
		minimum = min(minimum, (float)(depth-HALF_BOUNDING_BOX_DIAGONAL));
		maximum = max(maximum, (float)(depth+HALF_BOUNDING_BOX_DIAGONAL));
	}
	
	// Compute values
	increment = (maximum - minimum) / (count - 1);
	values[0] = minimum;
	for (int i=1; i<count; ++i) {
		values[i] = values[i-1] + increment;
	}
}

