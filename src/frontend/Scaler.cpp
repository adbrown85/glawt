/*
 * Scaler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scaler.hpp"


/** Creates a new Scaler using an axis. */
Scaler::Scaler(float x, float y, float z) {
	
	// Initialize attributes
	axis.set(x, y, z, 1.0);
	size = 1.0;
	
	// Initialize geometry
	BasicFactory::install();
	geometry = new Scene();
	if (x > 0.9) {
		geometry->open("${GANDER}/glsl/ScalerX.xml");
	} else if (y > 0.9) {
		geometry->open("${GANDER}/glsl/ScalerY.xml");
	} else {
		geometry->open("${GANDER}/glsl/ScalerZ.xml");
	}
	geometry->prepare();
	traverser = new Traverser(geometry);
}


Scaler::~Scaler() {
	
	delete geometry;
	delete traverser;
}


/** Draws the Scaler. */
void Scaler::draw() const {
	
	traverser->start();
}


/** Use the Scaler.
 * 
 * @param movement Difference between current and last cursor positions.
 * @param shapeID ID of the shape the Scaler is attached to.
 */
void Scaler::use(const Vector &movement, GLuint shapeID) {
	
	float dotProduct, pixelFactor, amount;
	Vector viewAxis;
	
	// Calculate translate amount
	pixelFactor = findPixelFactor(shapeID);
	viewAxis = Window::getRotationMatrix() * axis;
	dotProduct = dot(normalize(movement), normalize(viewAxis));
	amount = movement.length() * dotProduct * pixelFactor;
	
	// Translate selection
	if (fabs(dotProduct) > 0.5) {
		if (axis.x > 0.9)
			interpreter->run(Command::SCALE_X, amount);
		else if (axis.y > 0.9)
			interpreter->run(Command::SCALE_Y, amount);
		else
			interpreter->run(Command::SCALE_Z, amount);
	}
}

