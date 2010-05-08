/*
 * Shape.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>                         // For attributes
#include <map>                          // For attributes
#include "Matrix.hpp"
#include "Program.hpp"
#include "Drawable.hpp"
#include "Tag.hpp"
using namespace std;


/** Vertex attribute. */
struct Attribute {
	string name;
	GLint location, number;
};


/**
 * @ingroup basic
 * @brief Base class for a 3D object in the scene.
 * 
 * Uses a vertex buffer for drawing.
 * 
 * <table>
 * <tr>
 *   <td>count</td>
 *   <td>Number of elements in the shape.</td>
 * </tr>
 * <tr>
 *   <td>buffer</td>
 *   <td>Handle that OpenGL identifies the vertex buffer with.</td>
 * </tr>
 * <tr>
 *   <td>program</td>
 *   <td>Pointer to the Program the shape will be rendered with.</td>
 * </tr>
 * </table>
 */
class Shape : public Drawable {
public:
	Shape(const Tag &tag,
	      GLuint count,
	      list<string> attributes,
	      GLenum mode,
	      GLenum usage=GL_STATIC_DRAW);
	virtual void associate();
	virtual void draw() const;
	virtual void finalize();
	virtual void initAttributeValues() = 0;
protected:
	GLuint offset(int i) const;
protected: 
	list<Attribute> attributes;
	GLenum mode, usage;
	GLuint buffer, count;
	Program *program;
};


inline GLuint Shape::offset(int i) const {return i*count*3*sizeof(GLfloat);}

#endif

