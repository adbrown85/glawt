/*
 * Boolean.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Boolean.hpp"
float Boolean::FLT_INF;


/** Creates a new %Boolean node.
 * 
 * @throws Exception if @e of attribute not present
 * @throws Exception if @e operation attribute not present
 * @throws NodeException if float is not signed
 */
Boolean::Boolean(const Tag &tag,
                 ShapeTraits traits) : Hexahedron(tag,traits) {
	
	// Get tag attributes
	tag.get("of", of);
	tag.get("operation", operation);
	
	// Check operations will work correctly
	if (numeric_limits<float>::is_signed) {
		if (numeric_limits<float>::has_infinity) {
			FLT_INF = numeric_limits<float>::infinity();
		} else {
			FLT_INF = numeric_limits<float>::max();
		}
	} else {
		NodeException e(tag);
		e << "[Boolean] Cannot perform boolean without signed float.";
		throw e;
	}
}


/** Finds the group, shapes, and transforms needed by the operation.
 * 
 * @throws NodeException from Shape::associate()
 */
void Boolean::associate() {
	
	Hexahedron::associate();
	
	// Find nodes
	findGroup();
	findShapes();
	findTransforms();
}


/** Only draw the boolean operation if its output is tangible. */
void Boolean::draw() const {
	
	// Only draw if tangible
	if (tangible) {
		Hexahedron::draw();
	}
}


/** Updates and then creates the shape. */
void Boolean::finalize() {
	
	update();
	Hexahedron::finalize();
}


/** Finds the group the Boolean should look for shapes in. 
 * 
 * @throws NodeException if the group named by @e of cannot be found.
 */
void Boolean::findGroup() {
	
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Boolean] Could not find group named '" << of << "'.";
		throw e;
	}
}


/** Find texture unit that corresponds with the texture coordinates. */
UniformSampler* Boolean::findSampler(Shape *shape) {
	
	Node::iterator it;
	UniformSampler *sampler;
	
	for (it=shape->begin(); it!=shape->end(); ++it) {
		sampler = dynamic_cast<UniformSampler*>(*it);
		if (sampler != NULL)
			return sampler;
	}
	return NULL;
}


/** @throws NodeException if no shapes are in group. */
void Boolean::findShapes() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree under group for shapes
	q.push(group);
	while (!q.empty()) {
		node = q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL) {
			shapes.push_back(shape);
		}
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
	
	// Check
	if (shapes.size() == 0) {
		NodeException e(tag);
		e << "[Boolean] No shapes found in group.";
		throw e;
	}
}


/** Finds transforms in the group and listens for changes from them. */
void Boolean::findTransforms() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Transformation *transform;
	
	// Add listener to each transform
	q.push(group);
	while (!q.empty()) {
		node = q.front();
		transform = dynamic_cast<Transformation*>(node);
		if (transform != NULL)
			transform->addListener(this);
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


/** Only initialize all the attributes if the boolean output is tangible. */
void Boolean::initAttributes() {
	
	if (tangible) {
		Hexahedron::initAttributes();
	}
}


/** Determines if the shapes intersect each other using overlap attribute. */
bool Boolean::isOverlapped() {
	
	return min(overlap.upper,overlap.lower) == overlap.lower
	         && isSubstantial(overlap);
}


/** Determines if an extent is three dimensional. */
bool Boolean::isSubstantial(const Extent &extent) {
	
	return fabs(extent.diagonal.x) > 0.01
	         && fabs(extent.diagonal.y) > 0.01
	         && fabs(extent.diagonal.z) > 0.01;
}


/** Redo the operation when a Transformation has changed. */
void Boolean::nodeUpdated() {
	
	update();
	initAttributes();
}


/** @return string representing the node. */
string Boolean::toString() const {
	
	ostringstream stream;
	
	stream << getClassName();
	stream << " operation='" << operation << "'"
	       << " of='" << of << "'";
	return stream.str();
}


/** Boolean shape is not correct and must be recalculated. */
void Boolean::update() {
	
	updateExtents();
	updateOverlap();
	updateTangible();
}


/** Traverse the group and calculate extents for each shape. */
void Boolean::updateExtents() {
	
	// Collect extents of shapes in group
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	updateExtents(group);
	glPopMatrix();
}


/** Traverse a subtree and calculate extents for each shape. */
void Boolean::updateExtents(Node *node) {
	
	Node::iterator it;
	Transformation *transform;
	Shape *shape;
	
	// Apply and remove transform nodes
	if ((transform = dynamic_cast<Transformation*>(node))) {
		transform->apply();
		for (it=transform->begin(); it!=transform->end(); ++it)
			updateExtents(*it);
		transform->remove();
	}
	
	// Store shapes with extents
	else if ((shape = dynamic_cast<Shape*>(node))) {
		Extent extent;
		mvm = Transform::getModelViewMatrix();
		extent.upper = mvm * Vector(+0.5,+0.5,+0.5,1.0);
		extent.lower = mvm * Vector(-0.5,-0.5,-0.5,1.0);
		extent.diagonal = extent.upper - extent.lower;
		extent.label = shape->getID();
		extents[shape] = extent;
	}
	
	// Just do children
	else {
		for (it=node->begin(); it!=node->end(); ++it) {
			updateExtents(*it);
		}
	}
}


/** Find where the shapes overlap. */
void Boolean::updateOverlap() {
	
	map<Shape*,Extent>::iterator it;
	
	// Form shape
	overlap.upper = Vector(+FLT_INF);
	overlap.lower = Vector(-FLT_INF);
	for (it=extents.begin(); it!=extents.end(); ++it) {
		overlap.upper = min(overlap.upper, it->second.upper);
		overlap.lower = max(overlap.lower, it->second.lower);
	}
	overlap.diagonal = overlap.upper - overlap.lower;
}

