/*
 * Hexahedron.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Hexahedron.hpp"
bool Hexahedron::loaded=false;
int Hexahedron::indices[8][3];


Hexahedron::Hexahedron(const Tag &tag) : 
      Shape(tag, 24, getAttributes(), GL_QUADS) {
	
	if (!loaded)
		load();
};


void Hexahedron::initAttributeValues() {
	
	initPoints();
	initNormals();
	initCoords();
}


/** @return list of attributes used in the shape. */
list<string> Hexahedron::getAttributes() {
	
	list<string> attributes;
	
	attributes.push_back("MCVertex");
	attributes.push_back("MCNormal");
	attributes.push_back("TexCoord0");
	return attributes;
}


/** Maps vertex indices to points and texture coordinates. */
void Hexahedron::load() {
	
	int I[8][3] = {{2, 11, 21},   // 0 bottom-left-front
	               {3, 14, 20},   // 1 bottom-right-front
	               {1,  8, 18},   // 2 top-left-front
	               {0, 13, 19},   // 3 top-right-front
	               {7, 10, 22},   // 4 bottom-left-back
	               {6, 15, 23},   // 5 bottom-right-back
	               {4,  9, 17},   // 6 top-left-back
	               {5, 12, 16}};  // 7 top-right-back
	
	// Copy to class
	for (int i=0; i<8; ++i) {
		for (int j=0; j<3; ++j) {
			indices[i][j] = I[i][j];
		}
	}
}


/** Initializes the points in the vertex buffer.
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
void Hexahedron::initPoints() {
	
	GLfloat P[8][3] = {{-0.5, -0.5, +0.5},   // 0 bottom-left-front
	                   {+0.5, -0.5, +0.5},   // 1 bottom-right-front
	                   {-0.5, +0.5, +0.5},   // 2 top-left-front
	                   {+0.5, +0.5, +0.5},   // 3 top-right-front
	                   {-0.5, -0.5, -0.5},   // 4 bottom-left-back
	                   {+0.5, -0.5, -0.5},   // 5 bottom-right-back
	                   {-0.5, +0.5, -0.5},   // 6 top-left-back
	                   {+0.5, +0.5, -0.5}};  // 7 top-right-back
	GLfloat points[24][3];
	
	// Copy each point to each index it corresponds to
	int index;
	for (int p=0; p<8; ++p) {
		for (int j=0; j<3; ++j) {
			index = indices[p][j];
			for (int k=0; k<3; ++k) {
				points[index][k] = P[p][k];
			}
		}
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(0), sizeof(points), points);
}


/** Initializes the normals in the vertex buffer. */
void Hexahedron::initNormals() {
	
	GLfloat N[6][3] = {{ 0.0,  0.0, +1.0},     // front
	                   { 0.0,  0.0, -1.0},     // back
	                   {-1.0,  0.0,  0.0},     // left
	                   {+1.0,  0.0,  0.0},     // right
	                   { 0.0, +1.0,  0.0},     // top
	                   { 0.0, -1.0,  0.0}};    // bottom
	GLfloat normals[24][3];
	
	// Copy normals from faces to each index
	int index = -1;
	for (int n=0; n<6; ++n) {
		for (int j=0; j<4; ++j) {
			++index;
			for (int k=0; k<3; ++k)
				normals[index][k] = N[n][k];
		}
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(1), sizeof(normals), normals);
}

