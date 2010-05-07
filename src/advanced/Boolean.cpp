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
	findTransforms();
}


/** Calculates the operation. */
void Boolean::finalize() {
	
	// Initialize
	initBuffers();
	initIndices();
	
	// Make the shape
	calculate();
	updatePoints();
	updateCoords();
}


/** Traverse a subtree and modify extent using each shape. */
void Boolean::calculate() {
	
	// Reset
	upper = Vector(+FLT_INF);
	lower = Vector(-FLT_INF);
	inverses.clear();
	
	// Calculate
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	calculate(group);
	glPopMatrix();
	
	// Check if tangible
	tangible = (min(upper,lower) == lower);
}


/** Traverse a subtree and modify extent using each shape. */
void Boolean::calculate(Node *node) {
	
	Node::iterator it;
	Transformation *transform;
	Shape *shape;
	
	// Apply and remove transform nodes
	if ((transform = dynamic_cast<Transformation*>(node))) {
		transform->apply();
		for (it=transform->begin(); it!=transform->end(); ++it)
			calculate(*it);
		transform->remove();
	}
	
	// Update shapes
	else if ((shape = dynamic_cast<Shape*>(node))) {
		mvm = Transform::getModelViewMatrix();
		upper = min(mvm*Vector(+0.5,+0.5,+0.5,1.0), upper);
		lower = max(mvm*Vector(-0.5,-0.5,-0.5,1.0), lower);
		inverses[shape] = mvm.getInverse();
	}
	
	// Just do children
	else {
		for (it=node->begin(); it!=node->end(); ++it)
			calculate(*it);
	}
}


/** Draws the boolean shape. */
void Boolean::draw() const {
	
	// Stop if not tangible
	if (!tangible)
		return;
	
	// Enable buffer
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	
	// Enable attributes
	glEnableVertexAttribArray(POINT_LOCATION);
	glVertexAttribPointer(POINT_LOCATION, 3, GL_FLOAT, false, 0, (void*)0);
	
	// Draw
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
	
	// Disable attributes
	glDisableVertexAttribArray(POINT_LOCATION);
	
	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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


/** Finds transforms in the group and adds this as a listener. */
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


/** Creates the vertex buffers for the points and elements arrays. */
void Boolean::initBuffers() {
	
	// Points
	glGenBuffers(1, &dataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	
	// Indices
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
}


/** Initializes the elements array used in the vertex buffer.
 *
 * <pre>
 *     +-------+            9-------+         17-----16
 *    /|      /|           /|      /|        /|      /|  top
 *   1-------0 |          8-------+ |       18-----19 |
 *   | +-----|-+    left  | 10----|-+       | +-----|-+
 *   |/      |/           |/      |/        |/      |/
 *   2-------3            11------+         +-------+
 *     front
 *        back
 *     4-------5        +------12             +-------+
 *    /|      /|       /|      /|            /|      /|
 *   +-------+ |      +------13 |  right    +-------+ |
 *   | 7-----|-6      | +-----|15           | 22----|23
 *   |/      |/       |/      |/            |/      |/  bottom
 *   +-------+        +------14             21-----20
 * </pre>
 */
void Boolean::initIndices() {
	
	int v;
	GLubyte map[8][3] = {{2, 11, 21},   // 0 bottom-left-front
	                     {3, 14, 20},   // 1 bottom-right-front
	                     {1,  8, 18},   // 2 top-left-front
	                     {0, 13, 19},   // 3 top-right-front
	                     {7, 10, 22},   // 4 bottom-left-back
	                     {6, 15, 23},   // 5 bottom-right-back
	                     {4,  9, 17},   // 6 top-left-back
	                     {5, 12, 16}};  // 7 top-right-back
	
	for (int i=0; i<8; ++i) {
		for (int j=0; j<3; ++j) {
			v = map[i][j];
			indices[v] = i;
		}
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


/** Initializes the points array used in the vertex buffer.
 * 
 * <pre>
 *     6-------7
 *    /|      /|
 *   2-------3 |
 *   | 4-----|-5
 *   |/      |/
 *   0-------1
 * </pre>
 */
void Boolean::initPoints() {
	
	GLfloat points[8][3] = {{-0.5, -0.5, +0.5},   // 0 bottom-left-front
	                        {+0.5, -0.5, +0.5},   // 1 bottom-right-front
	                        {-0.5, +0.5, +0.5},   // 2 top-left-front
	                        {+0.5, +0.5, +0.5},   // 3 top-right-front
	                        {-0.5, -0.5, -0.5},   // 4 bottom-left-back
	                        {+0.5, -0.5, -0.5},   // 5 bottom-right-back
	                        {-0.5, +0.5, -0.5},   // 6 top-left-back
	                        {+0.5, +0.5, -0.5}};  // 7 top-right-back
	
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			this->points[i][j] = points[i][j];
		}
	}
}


/** One of the transforms was updated. */
void Boolean::nodeUpdated() {
	
	calculate();
	updatePoints();
	updateCoords();
}


/** @return string representing the node. */
string Boolean::toString() const {
	
	ostringstream stream;
	
	stream << Shape::toString();
	stream << " operation='" << operation << "'"
	       << " of='" << of << "'";
	return stream.str();
}


/** Updates the texture coordinates in the vertex buffer. */
void Boolean::updateCoords() {
	
	int id;
	map<Shape*,Matrix>::iterator it;
	Vector v;
	map<string,Vector*> vectors;
	map<string,Vector*>::iterator vi;
	
	if (!tangible)
		return;
	
	vectors["lower"] = &lower;
	vectors["upper"] = &upper;
	for (it=inverses.begin(); it!=inverses.end(); ++it) {
		for (vi=vectors.begin(); vi!=vectors.end(); ++vi) {
			id = it->first->getID();
			v = it->second*(*vi->second) + Vector(0.5,0.5,0.5,0);
			v.z = 1.0 - v.z;
			cout << id << " " << vi->first << ":" << v << endl;
		}
	}
}


/** Updates the points array used in the vertex buffer.
 * 
 * <pre>
 *     6-------7
 *    /|      /|
 *   2-------3 |
 *   | 4-----|-5
 *   |/      |/
 *   0-------1
 * </pre>
 */
void Boolean::updatePoints() {
	
	// Stop if not tangible
	if (!tangible)
		return;
	
	// Update points
	points[0][0] = lower.x; points[0][1] = lower.y; points[0][2] = upper.z;
	points[1][0] = upper.x; points[1][1] = lower.y; points[1][2] = upper.z;
	points[2][0] = lower.x; points[2][1] = upper.y; points[2][2] = upper.z;
	points[3][0] = upper.x; points[3][1] = upper.y; points[3][2] = upper.z;
	points[4][0] = lower.x; points[4][1] = lower.y; points[4][2] = lower.z;
	points[5][0] = upper.x; points[5][1] = lower.y; points[5][2] = lower.z;
	points[6][0] = lower.x; points[6][1] = upper.y; points[6][2] = lower.z;
	points[7][0] = upper.x; points[7][1] = upper.y; points[7][2] = lower.z;
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);
}

