/*
 * Calculator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP
#include "common.h"
#include "Shape.hpp"
#define HALF_BOUNDING_BOX_DIAGONAL 0.866025404
using namespace std;


/* Enumeration of different calculations. */
class Calculation {
public:
	enum {NONE, DISTRIBUTION_Z};
};

/** @brief Utility for calculating values from a set of shapes.
 * @ingroup basic
 */
class Calculator {
public:
	Calculator(set<Shape*> shapes);
	static GLint getCalculationFor(const string &name);
	void run(GLint calculation, GLsizei count, float *values);
	void setCanvas(Canvas *canvas);
protected:
	void checkCanvas();
	void runDistributionZ(GLsizei count, float *values);
private:
	Canvas *canvas;
	set<Shape*> shapes;
};

/** Sets the canvas if it is required by the calculation. */
inline void Calculator::setCanvas(Canvas *canvas) {this->canvas = canvas;}


#endif
