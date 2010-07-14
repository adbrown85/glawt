/*
 * Fullscreen.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Fullscreen.hpp"


/** Add uniform matrix child. */
Fullscreen::Fullscreen(const Tag &tag) : Shape(tag,getTraits()) {
	
	Node *node;
	string text;
	
	text = "uniform type='mat4' name='MVPMatrix' as='identity'";
	node = Factory::create(text);
	addChild(node);
}


ShapeTraits Fullscreen::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 4;
	traits.mode = GL_QUADS;
	traits.usage = GL_STATIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	return traits;
}


void Fullscreen::updateBuffer() {
	
	updateBufferCoords();
	updateBufferNormals();
	updateBufferPoints();
}


/** Initializes the static points array of the class. */
void Fullscreen::updateBufferPoints() {
	
	GLfloat points[4][3] = {{+1.0, +1.0, -1.0},
	                        {-1.0, +1.0, -1.0},
	                        {-1.0, -1.0, -1.0},
	                        {+1.0, -1.0, -1.0}};
	
	setBufferData("MCVertex", points);
}


/** Initializes the static indices array of the class. */
void Fullscreen::updateBufferNormals() {
	
	GLfloat normals[4][3] = {{0.0, 0.0, +1.0},
	                         {0.0, 0.0, +1.0},
	                         {0.0, 0.0, +1.0},
	                         {0.0, 0.0, +1.0}};
	
	setBufferData("MCNormal", normals);
}


/** Initializes the static coordinates array of the class. */
void Fullscreen::updateBufferCoords() {
	
	GLfloat coords[4][3] = {{1.0, 1.0, 0.0},
	                        {0.0, 1.0, 0.0},
	                        {0.0, 0.0, 0.0},
	                        {1.0, 0.0, 0.0}};
	
	setBufferData("TexCoord0", coords);
}

