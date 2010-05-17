/*
 * Translator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translator.hpp"


/** Creates a new Translator using an axis. */
Translator::Translator(float x, float y, float z) {
	
	// Initialize attributes
	axis.set(x, y, z, 1.0);
	size = 1.0;
	
	// Initialize geometry
	BasicFactory::install();
	geometry = new Scene();
	if (x > 0.9) {
		geometry->open("${GANDER}/glsl/TranslatorX.xml");
	} else if (y > 0.9) {
		geometry->open("${GANDER}/glsl/TranslatorY.xml");
	} else {
		geometry->open("${GANDER}/glsl/TranslatorZ.xml");
	}
	geometry->prepare();
	traverser = new Traverser(geometry);
}


Translator::~Translator() {
	
	delete geometry;
	delete traverser;
}


/** Draws the Translator. */
void Translator::draw() const {
	
	traverser->start();
}


/** Use the Translator.
 * 
 * @param movement Difference between current and last cursor positions.
 * @param shapeID ID of the shape the translator is attached to.
 */
void Translator::use(const Vector &movement, GLuint shapeID) {
	
	float dotProduct, pixelFactor, translateAmount;
	Vector viewAxis;
	
	// Calculate translate amount
	pixelFactor = findPixelFactor(shapeID);
	viewAxis = Window::getRotationMatrix() * axis;
	dotProduct = dot(normalize(movement), normalize(viewAxis));
	translateAmount = movement.length() * dotProduct * pixelFactor;
	
	// Translate selection
	if (fabs(dotProduct) > 0.5) {
		if (axis.x > 0.9)
			interpreter->run(Command::TRANSLATE_X, translateAmount);
		else if (axis.y > 0.9)
			interpreter->run(Command::TRANSLATE_Y, translateAmount);
		else
			interpreter->run(Command::TRANSLATE_Z, translateAmount);
	}
}

