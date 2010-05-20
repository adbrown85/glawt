/*
 * Translator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translator.hpp"


/** Creates a new Translator using an axis. */
Translator::Translator(float x, float y, float z) {
	
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
			filename += "/glsl/TranslatorX.xml";
			geometry->open(filename);
		} else if (y > 0.9) {
			filename += "/glsl/TranslatorY.xml";
			geometry->open(filename);
		} else {
			filename += "/glsl/TranslatorZ.xml";
			geometry->open(filename);
		}
		geometry->prepare();
		traverser = new Traverser(geometry);
	} catch (Exception e) {
		delete geometry;
		geometry = NULL;
		traverser = NULL;
		cerr << "[Translator] Problem opening '" << filename << "'." << endl;
		cerr << "[Translator] May not be able to translate with mouse." << endl;
		cerr << "[Translator] Try installing Gander again." << endl;
	}
}


Translator::~Translator() {
	
	if (geometry != NULL) {
		delete geometry;
	}
	if (traverser != NULL) {
		delete traverser;
	}
}


/** Draws the Translator. */
void Translator::draw() const {
	
	if (traverser != NULL) {
		traverser->start();
	}
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

