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
Boolean::Boolean(const Tag &tag) : Shape(tag) {
	
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


/** Finds the group and shapes needed by the operation.
 * 
 * @throws NodeException from Shape::associate()
 */
void Boolean::associate() {
	
	Shape::associate();
	
	// Find nodes
	findGroup();
	findShapes();
}


/** Traverse a subtree and modify extent using each shape. */
void Boolean::calculate(Node *node,
                        Vector &upper,
                        Vector &lower) const {
	
	Matrix mvm;
	Node::iterator it;
	Transformation *transform;
	Shape *shape;
	Vector v;
	
	// Apply and remove transform nodes
	if ((transform = dynamic_cast<Transformation*>(node))) {
		transform->apply();
		for (it=transform->begin(); it!=transform->end(); ++it)
			calculate(*it, upper, lower);
		transform->remove();
	}
	
	// Update shapes
	else if ((shape = dynamic_cast<Shape*>(node))) {
		mvm = Transform::getModelViewMatrix();
		v = mvm * Vector(+0.5,+0.5,+0.5,1.0);
		upper = min(v, upper);
		v = mvm * Vector(-0.5,-0.5,-0.5,1.0);
		lower = max(v, lower);
	}
	
	// Just do children
	else {
		for (it=node->begin(); it!=node->end(); ++it)
			calculate(*it, upper, lower);
	}
}


/**
 * To perform the boolean operation for cubes we first need to find the 
 * positions of their minimum and maximum bounding corners.  Basically that 
 * means for each shape we multiply the model matrix by [-0.5,-0.5,-0.5] and 
 * [+0.5,+0.5,+0.5].  Of course, that means traversing from the start of group 
 * and applying each transformation.  Then when a shape is found we do the 
 * multiplications and compare them to the current ones.
 * 
 * A big problem however is how do you apply the transformations.  Currently 
 * they just call the corresponding OpenGL functions, so they operate directly 
 * on the OpenGL ModelView matrix itself.
 * 
 * One way to do this as is would be to push the modelview matrix and load the 
 * identity before starting.  Then apply each of the transformations 
 * normally.  When a shape is found retrieve a Matrix object using 
 * Transform::getModelViewMatrix() and do the multiplications.
 * 
 * Another way to approach the problem is to have the transformations override 
 * an applyTo(Matrix&) method.  Then for each transformation you would just 
 * pass the current matrix to it and it would perform the mathematical 
 * calculation for it.  There would have to be a corresponding 
 * removeFrom(Matrix&) method though, which is where it starts to get a little 
 * hairy.  We could make the method pass a stack<Matrix>& instead.  That way 
 * you wouldn't have to worry about the inversion.
 * 
 * A third solution might be to implement two new classes.  The first would be 
 * a MatrixStack class that replicates the OpenGL matrix behavior but with my 
 * regular Matrix class and an STL stack.  Then a new Root class would hold 
 * one of those and provide some methods for accessing it.  That way all the 
 * transformations and uniforms could find it and perform their required 
 * operations very easily.
 * 
 * The first might be the quickest solution right now but the last seems like 
 * the best long term.
 */
void Boolean::draw() const {
	
	Vector upper(+FLT_INF), lower(-FLT_INF);
	
	// Calculate
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	calculate(group, upper, lower);
	glPopMatrix();
	
	// Print
	cout << "Upper: " << upper << endl;
	cout << "Lower: " << lower << endl;
	if (min(upper,lower) == lower) {
		cout << "Intersection!" << endl;
	} else {
		cout << "No intersection." << endl;
	}
}


/** @throws NodeException if the group named by @e of cannot be found. */
void Boolean::findGroup() {
	
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Boolean] Could not find group named '" << of << "'.";
		throw e;
	}
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
		if (shape != NULL)
			shapes.push_back(shape);
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
	
	// Check
	if (shapes.empty()) {
		NodeException e(tag);
		e << "[Boolean] No shapes found in group.";
		throw e;
	}
}


/** @return string representing the node. */
string Boolean::toString() const {
	
	ostringstream stream;
	
	stream << Shape::toString();
	stream << " operation='" << operation << "'"
	       << " of='" << of << "'";
	return stream.str();
}

