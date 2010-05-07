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


/** Creates the shape. */
void Boolean::finalize() {
	
	// Initialize
	initBuffers();
	initIndices();
	nodeUpdated();
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
	
	int count;
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree under group for shapes
	count = 0;
	q.push(group);
	while (!q.empty()) {
		node = q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL)
			++count;
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
	
	// Check
	if (count == 0) {
		NodeException e(tag);
		e << "[Boolean] No shapes found in group.";
		throw e;
	}
}


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
	updateUpperLower();
	updateTangible();
	if (tangible) {
		updatePoints();
		updateCoords();
	}
}


/** Updates the texture coordinates in the vertex buffer. */
void Boolean::updateCoords() {
	
	Coordinates coords;
	map<Shape*,Extent>::iterator it;
	UniformSampler *sampler;
	
	// Calculate texture coords
	for (it=extents.begin(); it!=extents.end(); ++it) {
		sampler = findSampler(it->first);
		coords.upper = (upper - it->second.lower) / it->second.diagonal;
		coords.upper.z = 1.0 - coords.upper.z;
		coords.lower = (lower - it->second.lower) / it->second.diagonal;
		coords.lower.z = 1.0 - coords.lower.z;
		units[sampler->getValue()] = coords;
	}
	
	// Print
	map<int,Coordinates>::iterator ui;
	for (ui=units.begin(); ui!=units.end(); ++ui) {
		cout << ui->first << ": "
		     << ui->second.lower << " - "
		     << ui->second.upper << endl;
	}
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
		extents[shape] = extent;
	}
	
	// Just do children
	else {
		for (it=node->begin(); it!=node->end(); ++it) {
			updateExtents(*it);
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


/** Checks that the shape formed by the operation can be shown. */
void Boolean::updateTangible() {
	
	tangible = (min(upper,lower) == lower);
}


/** Find the extent of the boolean operation. */
void Boolean::updateUpperLower() {
	
	map<Shape*,Extent>::iterator it;
	
	// Form shape
	upper = Vector(+FLT_INF);
	lower = Vector(-FLT_INF);
	for (it=extents.begin(); it!=extents.end(); ++it) {
		upper = min(upper, it->second.upper);
		lower = max(lower, it->second.lower);
	}
}

