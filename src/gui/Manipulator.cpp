/*
 * Manipulator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Manipulator.hpp"


/** Creates a manipulator that cannot send commands yet.
 * 
 * @param axis Either 'x', 'y', or 'z'.
 * @param command Command to run.
 * @param filename Path in data directory containing widget geometry.
 * @param bias Multiplier to the default movement amount.
 * @param warning Text to print if cannot find widget file.
 */
Manipulator::Manipulator(char axis,
                         int command,
                         string filename,
                         float bias,
                         const string &warning) {
	
	// Initialize
	this->command = command;
	this->enabled = true;
	this->delegate = NULL;
	this->bias = bias;
	
	// Initialize axis and offset
	switch (tolower(axis)) {
	case 'x': this->axis = Vector(1,0,0,1); break;
	case 'y': this->axis = Vector(0,1,0,1); break;
	case 'z': this->axis = Vector(0,0,1,1); break;
	default:
		throw Exception("[Manipulator] Unexpected axis.");
	}
	offset = this->axis * 0.5;
	offset.w = 1.0;
	
	// Initialize widget
	try {
		widget = new Scene();
		widget->open(Resources::get(filename));
		widget->prepare();
		traverser = new Traverser(widget);
	} catch (Exception e) {
		delete widget;
		widget = NULL;
		traverser = NULL;
		glog << "[Manipulator] Problem opening '" << filename << "'." << endl;
		glog << "[Manipulator] " << warning << endl;
		glog << "[Manipulator] Try installing Gander again." << endl;
	}
}


/** Cleans up the widget. */
Manipulator::~Manipulator() {
	
	if (widget != NULL)
		delete widget;
	if (traverser != NULL)
		delete traverser;
}


/** Calculates how a pixel compares to a global unit.
 * 
 * @param canvas Canvas to take camera position from.
 * @param shapeID ID of the shape to use for the depth component.
 */
float Manipulator::findPixelFactor(Canvas *canvas, GLuint shapeID) {
	
	float pixelsPerUnit, depth, screenX;
	Node *node;
	Vector clip, proj;
	
	// Get depth of the shape
	node = dynamic_cast<Node*>(Identifiable::findByID(shapeID));
	depth = node->getDepth() + canvas->getCamera()->getPosition().z;
	
	// Transform unit vector at that depth to clip space
	proj = State::getProjectionMatrix() * Vector(1,0,depth,1);
	clip = proj / proj.w;
	
	// Calculate how many pixels that represents on screen
	screenX = ((clip.x + 1.0) * 0.5) * canvas->getWidth();
	pixelsPerUnit = screenX - (canvas->getWidth() * 0.5);
	return 1 / pixelsPerUnit;
}


/** Draws the manipulator around @e transformable in @e canvas. */
void Manipulator::draw(Transformable *transformable, Canvas *canvas) const {
	
	// Make sure widget was loaded correctly
	if (traverser == NULL)
		return;
	
	// Draw at position
	State::setMode(MODEL_MODE);
	State::push();
	State::loadIdentity();
	State::apply(getBaseMatrix(transformable));
	traverser->start();
	State::pop();
}


Vector Manipulator::getBase(Transformable *transformable) const {
	
	Vector diagonal;
	
	// Compute base
	diagonal = transformable->getExtent().diagonal;
	return transformable->getPosition() + (diagonal * offset);
}


Matrix Manipulator::getBaseMatrix(Transformable *transformable) const {
	
	Vector base;
	
	// Compute and return as translation matrix
	base = getBase(transformable);
	return Matrix(1.0, 0.0, 0.0, base.x,
	              0.0, 1.0, 0.0, base.y,
	              0.0, 0.0, 1.0, base.z,
	              0.0, 0.0, 0.0, 1.0);
}


Vector Manipulator::getHotspot(Transformable *transformable) const {
	
	return getBase(transformable) + offset;
}


Matrix Manipulator::getHotspotMatrix(Transformable *transformable) const {
	
	Vector hotspot;
	
	hotspot = getHotspot(transformable);
	return Matrix(1.0, 0.0, 0.0, hotspot.x,
	              0.0, 1.0, 0.0, hotspot.y,
	              0.0, 0.0, 1.0, hotspot.z,
	              0.0, 0.0, 0.0, 1.0);
}


/** Use the manipulator.
 * 
 * @param movement Difference between current and last cursor positions.
 * @param shapeID ID of the shape the manipulator is attached to.
 * @param canvas Canvas to take camera position from.
 */
void Manipulator::use(const Vector &movement, GLuint shapeID, Canvas *canvas) {
	
	float dotProduct, pixelFactor, amount;
	Vector viewAxis;
	
	// Calculate amount
	pixelFactor = findPixelFactor(canvas, shapeID);
	viewAxis = canvas->getCamera()->getRotation() * axis;
	dotProduct = dot(normalize(movement), normalize(viewAxis));
	amount = movement.length() * dotProduct * pixelFactor;
	
	// Perform command
	if (fabs(dotProduct) > 0.5) {
		delegate->run(command, amount * bias);
	}
}

