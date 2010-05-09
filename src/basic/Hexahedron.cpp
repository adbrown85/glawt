/*
 * Hexahedron.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Hexahedron.hpp"
bool Hexahedron::loaded=false;
int Hexahedron::indices[8][3];


Hexahedron::Hexahedron(const Tag &tag,
                       ShapeTraits traits) : Shape(tag,traits) {
	
	if (!loaded) {
		load();
		loaded = true;
	}
};


/** @return list of attributes used in the shape. */
ShapeTraits Hexahedron::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 24;
	traits.mode = GL_QUADS;
	traits.usage = GL_STATIC_DRAW;
	traits.addAttribute("MCVertex");
	traits.addAttribute("MCNormal");
	traits.addAttribute("TexCoord0");
	return traits;
}


/** Initializes the points, normals, and coordinates. */
void Hexahedron::initAttributes() {
	
	initPoints();
	initNormals();
	initCoords();
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
	
/*
	GLfloat P[8][3] = {{-0.5, -0.5, +0.5},   // 0 bottom-left-front
	                   {+0.5, -0.5, +0.5},   // 1 bottom-right-front
	                   {-0.5, +0.5, +0.5},   // 2 top-left-front
	                   {+0.5, +0.5, +0.5},   // 3 top-right-front
	                   {-0.5, -0.5, -0.5},   // 4 bottom-left-back
	                   {+0.5, -0.5, -0.5},   // 5 bottom-right-back
	                   {-0.5, +0.5, -0.5},   // 6 top-left-back
	                   {+0.5, +0.5, -0.5}};  // 7 top-right-back
*/
	GLfloat points[24][3];
	
	// Fill array from corners
	toArray(points, Vector(-0.5,-0.5,-0.5),Vector(+0.5,+0.5,+0.5));
	
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


/** Fills an array of points with values from two min and max bounds.
 * 
 * @param array Array of points to fill
 * @param l Lower corner of the shape
 * @param u Upper corner of the shape
 */
void Hexahedron::toArray(float array[24][3],
                         const Vector &l,
                         const Vector &u) {
	
	GLfloat P[8][3];
	int index;
	
	// Form eight points on corners
	P[0][0] = l.x;  P[0][1] = l.y;  P[0][2] = u.z;
	P[1][0] = u.x;  P[1][1] = l.y;  P[1][2] = u.z;
	P[2][0] = l.x;  P[2][1] = u.y;  P[2][2] = u.z;
	P[3][0] = u.x;  P[3][1] = u.y;  P[3][2] = u.z;
	P[4][0] = l.x;  P[4][1] = l.y;  P[4][2] = l.z;
	P[5][0] = u.x;  P[5][1] = l.y;  P[5][2] = l.z;
	P[6][0] = l.x;  P[6][1] = u.y;  P[6][2] = l.z;
	P[7][0] = u.x;  P[7][1] = u.y;  P[7][2] = l.z;
	
	// Copy each point to indexed points in array
	for (int p=0; p<8; ++p) {
		for (int j=0; j<3; ++j) {
			index = indices[p][j];
			for (int k=0; k<3; ++k) {
				array[index][k] = P[p][k];
			}
		}
	}
}


