/*
 * Square.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#include "Program.hpp"
#include "Shape.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief
 *     2D square shape that can be drawn by %Display.
 */
class Square : public Shape {
public:
	Square(const Tag &tag);
	virtual void draw() const;
protected:
	virtual void initBuffers();
	virtual void initCoords();
	virtual void initIndices();
	virtual void initNormals();
	virtual void initPoints();
private:
	static bool loaded;
	static GLfloat coords[4][3], normals[4][3], points[4][3];
	static GLint coordsOffset, normalsOffset, pointsOffset;
	static GLuint dataBuffer, indicesBuffer;
	static GLushort indices[4];
};


#endif
