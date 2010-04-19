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


Cube::Cube(const Tag &tag) :
           Shape(tag) {
	
	// Class name
	className = "Cube";
	
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
	
	// Enable buffers and arrays
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glEnableVertexAttribArray(pointsLoc);
	glEnableVertexAttribArray(normalsLoc);
	glEnableVertexAttribArray(coordsLoc);
	
	// Draw
	glVertexAttribPointer(pointsLoc, 3, GL_FLOAT, false, 0, (void*)pointsOffset);
	glVertexAttribPointer(normalsLoc, 3, GL_FLOAT, false, 0, (void*)normalsOffset);
	if (style == GL_TEXTURE_2D)
		glVertexAttribPointer(coordsLoc, 3, GL_FLOAT, false, 0, (void*)coords2dOffset);
	else
		glVertexAttribPointer(coordsLoc, 3, GL_FLOAT, false, 0, (void*)coords3dOffset);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
	
	// Disable buffers and arrays
	glDisableVertexAttribArray(pointsLoc);
	glDisableVertexAttribArray(normalsLoc);
	glDisableVertexAttribArray(coordsLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


/**
 * Finds vertex attribute locations in the current shader program.
 * 
 * @note Does not throw an error in case shaders do not use an attribute.
 */
void Cube::finalize() {
	
	Program *program;
	
	// Find locations in program
	program = Program::find(parent);
	pointsLoc = glGetAttribLocation(program->getHandle(), "MCVertex");
	normalsLoc = glGetAttribLocation(program->getHandle(), "MCNormal");
	coordsLoc = glGetAttribLocation(program->getHandle(), "TexCoord0");
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
				coords2d[m][c] = coords[i][c];
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
				coords3d[m][c] = coords[i][c];
		}
	}
}


/**
 * Initializes the indices used to draw the box's faces.
 */
void Cube::initIndices() {
	
	// Copy to class
	for (int i=0; i<24; ++i)
		this->indices[i] = i;
}


/**
 * Determines which points correspond to the standard eight points of a cube.
 */
void Cube::initMap() {
	
	GLubyte map[8][3] = {{1,  8, 18},
	                     {0, 13, 19},
	                     {2, 11, 23},
	                     {3, 14, 22},
	                     {4,  9, 17},
	                     {5, 12, 16},
	                     {7, 10, 20},
	                     {6, 15, 21}};
	
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


/**
 * Initializes the %Cube class's static points array.
 */
void Cube::initPoints() {
	
	GLfloat points[8][3] = {{-0.5, +0.5, +0.5},
	                        {+0.5, +0.5, +0.5},
	                        {-0.5, -0.5, +0.5},
	                        {+0.5, -0.5, +0.5},
	                        {-0.5, +0.5, -0.5},
	                        {+0.5, +0.5, -0.5},
	                        {-0.5, -0.5, -0.5},
	                        {+0.5, -0.5, -0.5}};
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

