/*
 * Scaler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scaler.hpp"


/** Creates a new Scaler using an axis. */
Scaler::Scaler(float x, float y, float z) {
	
	string filename(GANDER_DATA_DIR);
	
	// Initialize attributes
	axis.set(x, y, z, 1.0);
	size = 1.0;
	geometry = NULL;
	traverser = NULL;
	
	// Initialize geometry
	BasicFactory::install();
	try {
		geometry = new Scene();
		if (x > 0.9) {
			filename += "/glsl/ScalerX.xml";
			geometry->open(filename);
		} else if (y > 0.9) {
			filename += "/glsl/ScalerY.xml";
			geometry->open(filename);
		} else {
			filename += "/glsl/ScalerZ.xml";
			geometry->open(filename);
		}
		geometry->prepare();
		traverser = new Traverser(geometry);
	} catch (Exception e) {
		delete geometry;
		geometry = NULL;
		traverser = NULL;
		cerr << "[Scaler] Problem opening '" << filename << "'." << endl;
		cerr << "[Scaler] May not be able to scale with mouse." << endl;
		cerr << "[Scaler] Try installing Gander again." << endl;
	}
}


Scaler::~Scaler() {
	
	if (geometry != NULL) {
		delete geometry;
	}
	if (traverser != NULL) {
		delete traverser;
	}
}


/** Draws the Scaler. */
void Scaler::draw() const {
	
	if (traverser != NULL) {
		traverser->start();
	}
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

