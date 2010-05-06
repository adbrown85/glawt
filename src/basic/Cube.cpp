/*
 * Cube.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"
bool Cube::loaded = false;
GLint Cube::pointsOffset, Cube::normalsOffset;
GLint Cube::coords2dOffset, Cube::coords3dOffset;
GLfloat Cube::points[24][3], Cube::normals[24][3];
GLfloat Cube::coords2d[24][3], Cube::coords3d[24][3];
GLubyte Cube::map[8][3];
GLuint Cube::indicesBuffer=0, Cube::dataBuffer=0;
GLushort Cube::indices[24];


Cube::Cube(const Tag &tag) : Shape(tag) {
	
	// Attributes
	if (!loaded) {
		initIndices();
		initMap();
		initPoints();
		initNormals();
		initCoords2d();
		initCoords3d();
		initBuffers();
		loaded = true;
	}
}


void Cube::draw() const {
	
	// Enable buffers
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	
	// Enable attributes
	glEnableVertexAttribArray(POINT_LOCATION);
	glVertexAttribPointer(POINT_LOCATION, 3, GL_FLOAT, false, 0, (void*)pointsOffset);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, false, 0, (void*)normalsOffset);
	glEnableVertexAttribArray(COORD_LOCATION);
	switch (style) {
	case GL_TEXTURE_2D:
		glVertexAttribPointer(COORD_LOCATION, 3, GL_FLOAT, false, 0, (void*)coords2dOffset);
		break;
	case GL_TEXTURE_3D:
		glVertexAttribPointer(COORD_LOCATION, 3, GL_FLOAT, false, 0, (void*)coords3dOffset);
		break;
	}
	
	// Draw
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
	
	// Disable attributes
	glDisableVertexAttribArray(POINT_LOCATION);
	glDisableVertexAttribArray(COORD_LOCATION);
	glDisableVertexAttribArray(NORMAL_LOCATION);
	
	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Cube::initBuffers() {
	
	int dataSize;
	
	// Calculate sizes and offsets
	dataSize = sizeof(points) + sizeof(normals) + sizeof(coords2d) + sizeof(coords3d);
	pointsOffset = 0;
	normalsOffset = pointsOffset + sizeof(points);
	coords2dOffset = normalsOffset + sizeof(normals);
	coords3dOffset = coords2dOffset + sizeof(coords2d);
	
	// Points and coordinates
	glGenBuffers(1, &dataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, pointsOffset, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, normalsOffset, sizeof(normals), normals);
	glBufferSubData(GL_ARRAY_BUFFER, coords2dOffset, sizeof(coords2d), coords2d);
	glBufferSubData(GL_ARRAY_BUFFER, coords3dOffset, sizeof(coords3d), coords3d);
	
	// Indices
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void Cube::initCoords2d() {
	
	GLfloat coords[4][3] = {{0.0, 0.0, 0.0},
	                        {0.0, 1.0, 0.0},
	                        {1.0, 0.0, 0.0},
	                        {1.0, 1.0, 0.0}};
	GLubyte map[4][6] = {{ 1,  5,  9, 13, 17, 21},
	                     { 2,  6, 10, 14, 18, 22},
	                     { 0,  4,  8, 12, 16, 20},
	                     { 3,  7, 11, 15, 19, 23}};
	int m;
	
	// Copy to class
	for (int i=0; i<4; i++) {
		for (int v=0; v<6; v++) {
			m = map[i][v];
			for (int c=0; c<3; c++)
				this->coords2d[m][c] = coords[i][c];
		}
	}
}


/**
 * Initializes the %Cube class's static coordinates array.
 */
void Cube::initCoords3d() {
	
	GLfloat coords[8][3] = {{0.0, 1.0, 1.0},
	                        {1.0, 1.0, 1.0},
	                        {0.0, 0.0, 1.0},
	                        {1.0, 0.0, 1.0},
	                        {0.0, 1.0, 0.0},
	                        {1.0, 1.0, 0.0},
	                        {0.0, 0.0, 0.0},
	                        {1.0, 0.0, 0.0}};
	int m;
	
	// Copy to class
	for (int i=0; i<8; ++i) {
		for (int v=0; v<3; ++v) {
			m = map[i][v];
			for (int c=0; c<3; ++c)
				this->coords3d[m][c] = coords[i][c];
		}
	}
}


/** Initializes the indices used to draw the box's faces. */
void Cube::initIndices() {
	
	// Copy to class
	for (int i=0; i<24; ++i)
		this->indices[i] = i;
}


/** Determines which points correspond to the standard 8 points of a cube.
 *
 * <pre>
 *       front        left                  top
 *     1-------0        8-------+        18-----19
 *    /|      /|       /|      /|       /|      /|
 *   +-------+ |      9-------+ |      17-----16 |
 *   | 2-----|-3      | 11----|-+      | +-----|-+
 *   |/      |/       |/      |/       |/      |/
 *   +-------+        10------+        +-------+
 * 
 *     +-------+        +------13        +-------+
 *    /|      /|       /|      /|       /|      /|
 *   4-------5 |      +------12 |      +-------+ |
 *   | +-----|-+      | +-----|14      | 23----|22
 *   |/      |/       |/      |/       |/      |/
 *   7-------6        +------15        20-----21
 *      back                 right      bottom
 * </pre>
 */
void Cube::initMap() {
	
	                   // FB  LR  TB
	GLubyte map[8][3] = {{ 1,  8, 18},   // 0 top-left (back)
	                     { 0, 13, 19},   // 1 top-right (back)
	                     { 2, 11, 23},   // 2 bottom-left (back)
	                     { 3, 14, 22},   // 3 bottom-right (back)
	                     { 4,  9, 17},   // 4 top-left (front)
	                     { 5, 12, 16},   // 5 top-right (front)
	                     { 7, 10, 20},   // 6 bottom-left (front)
	                     { 6, 15, 21}};  // 7 bottom-right (front)
	
	// Copy to class
	for (int i=0; i<8; ++i)
		for (int j=0; j<3; ++j)
			this->map[i][j] = map[i][j];
}


void Cube::initNormals() {
	
	GLfloat normals[6][3] = {{ 0.0,  0.0, +1.0},     // front
	                         { 0.0,  0.0, -1.0},     // back
	                         {-1.0,  0.0,  0.0},     // left
	                         {+1.0,  0.0,  0.0},     // right
	                         { 0.0, +1.0,  0.0},     // top
	                         { 0.0, -1.0,  0.0}};    // bottom
	int m;
	
	// Copy to class
	for (int f=0; f<6; ++f) {
		for (int v=0; v<4; ++v) {
			m = f * 4 + v;
			for (int c=0; c<3; c++)
				this->normals[m][c] = normals[f][c];
		}
	}
}


/** Initializes the %Cube class's static points array.
 * 
 * <pre>
 *     0-------1
 *    /|      /|
 *   4-------5 |
 *   | 2-----|-3
 *   |/      |/
 *   6-------7
 * </pre>
 */
void Cube::initPoints() {
	
	GLfloat points[8][3] = {{-0.5, +0.5, +0.5},   // 0 top-left (back)
	                        {+0.5, +0.5, +0.5},   // 1 top-right (back)
	                        {-0.5, -0.5, +0.5},   // 2 bottom-left (back)
	                        {+0.5, -0.5, +0.5},   // 3 bottom-right (back)
	                        {-0.5, +0.5, -0.5},   // 4 top-left (front)
	                        {+0.5, +0.5, -0.5},   // 5 top-right (front)
	                        {-0.5, -0.5, -0.5},   // 6 bottom-left (front)
	                        {+0.5, -0.5, -0.5}};  // 7 bottom-right (front)
	int m;
	
	// Copy to class
	for (int i=0; i<8; ++i) {
		for (int v=0; v<3; ++v) {
			m = map[i][v];
			for (int c=0; c<3; ++c)
				this->points[m][c] = points[i][c];
		}
	}
}

