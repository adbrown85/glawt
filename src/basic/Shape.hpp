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
#include "Matrix.hpp"
#include "Program.hpp"
#include "Drawable.hpp"
#include "Tag.hpp"
using namespace std;


/* Vertex attribute. */
struct VertexAttribute {
	string name;
	GLint location, number;
};

/* Shape parameters. */
struct ShapeTraits {
	GLuint count;
	list<string> attributes;
	GLenum mode, usage;
	void addAttribute(const string &name) {attributes.push_back(name);}
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
	Shape(const Tag &tag, ShapeTraits traits);
	virtual void associate();
	virtual void draw() const;
	virtual void finalize();
	virtual string getName() const;
	virtual string toString() const;
protected:
	virtual void initAttributes() = 0;
	GLuint offset(int i) const;
protected: 
	list<VertexAttribute> attributes;
	GLenum mode, usage;
	GLuint buffer, count;
	Program *program;
	string name;
};


/** @return position in the buffer for the i'th attribute. */
inline GLuint Shape::offset(int i) const {return i*count*3*sizeof(GLfloat);}

/** @return user-assigned name of the shape. */
inline string Shape::getName() const {return name;}

#endif

