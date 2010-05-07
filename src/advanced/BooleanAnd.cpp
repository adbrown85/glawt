/*
 * BooleanAnd.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanAnd.hpp"


BooleanAnd::BooleanAnd(const Tag &tag) : Boolean(tag) {
	
	
}


/** Draws the boolean shape. */
void BooleanAnd::draw() const {
	
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
void BooleanAnd::initIndices() {
	
	int v;
	GLubyte map[8][3] = {{2, 11, 21},   // 0 bottom-left-front
	                     {3, 14, 20},   // 1 bottom-right-front
	                     {1,  8, 18},   // 2 top-left-front
	                     {0, 13, 19},   // 3 top-right-front
	                     {7, 10, 22},   // 4 bottom-left-back
	                     {6, 15, 23},   // 5 bottom-right-back
	                     {4,  9, 17},   // 6 top-left-back
	                     {5, 12, 16}};  // 7 top-right-back
	
	// Copy to indices
	for (int i=0; i<8; ++i) {
		for (int j=0; j<3; ++j) {
			v = map[i][j];
			indices[v] = i;
		}
	}
	
	// Send to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
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
void BooleanAnd::initPoints() {
	
	GLfloat p[8][3] = {{-0.5, -0.5, +0.5},   // 0 bottom-left-front
	                   {+0.5, -0.5, +0.5},   // 1 bottom-right-front
	                   {-0.5, +0.5, +0.5},   // 2 top-left-front
	                   {+0.5, +0.5, +0.5},   // 3 top-right-front
	                   {-0.5, -0.5, -0.5},   // 4 bottom-left-back
	                   {+0.5, -0.5, -0.5},   // 5 bottom-right-back
	                   {-0.5, +0.5, -0.5},   // 6 top-left-back
	                   {+0.5, +0.5, -0.5}};  // 7 top-right-back
	
	// Copy to points
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			points[i][j] = p[i][j];
		}
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);
}


/** Updates the texture coordinates in the vertex buffer. */
void BooleanAnd::updateCoords() {
	
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
void BooleanAnd::updatePoints() {
	
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
void BooleanAnd::updateTangible() {
	
	tangible = (min(upper,lower) == lower);
}

