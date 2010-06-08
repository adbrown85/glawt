/*
 * Shape.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "common.h"
#include "SimpleDrawable.hpp"
#include "Matrix.hpp"
#include "Program.hpp"
#include "Transformation.hpp"
#include "Transform.hpp"
#include "UniformMatrix.hpp"
#include "Factory.hpp"
using namespace std;


/* Vertex attribute. */
struct VertexAttribute {
	string name;
	GLint location, number;
	GLuint offset;
};

/* Shape parameters. */
struct ShapeTraits {
	GLuint count;
	list<string> attributes;
	GLenum mode, usage;
};


/** @brief Base class for a 3D object in the scene.
 * 
 * Uses a vertex buffer for drawing.  If <i>usage</i> is 
 * <tt>GL_STATIC_DRAW</tt>, a buffer will only be generated once for each 
 * concrete shape.  Subsequent instances of that shape will be given the same 
 * buffer.  That way duplicate buffers are avoided.
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
 * 
 * @ingroup basic
 */
class Shape : public SimpleDrawable {
public:
	Shape(const Tag &tag, ShapeTraits traits);
	virtual void associate();
	virtual void draw() const;
	void draw(int first, int number) const;
	virtual void finalize();
	virtual list<VertexAttribute> getAttributes() const;
	virtual GLuint getCount() const;
	virtual GLuint getLimit() const;
	virtual string getName() const;
	virtual Program* getProgram() const;
	virtual void setAttributes(list<VertexAttribute> &attributes);
	virtual void setProgram(Program *program);
	virtual string toString() const;
protected:
	void checkForDefaultUniforms();
	virtual GLuint getOffset(const string &name) const;
	static bool isBufferStored(const string &className);
	void setBufferData(const string &name, GLfloat data[][3]);
	virtual void setCount(GLuint count);
	virtual void setLimit(GLuint limit);
	virtual void updateBuffer() = 0;
private:
	bool defaults;
	list<VertexAttribute> attributes;
	GLenum mode, usage;
	GLuint block, buffer, count, limit;
	static map<string,GLuint> buffers;
	map<string,GLuint> offsets;
	Program *program;
	string name;
};

/** @return Attributes in use for this shape. */
inline list<VertexAttribute> Shape::getAttributes() const {return attributes;}

/** @return Number of vertices in the shape. */
inline GLuint Shape::getCount() const {return count;}

/** @return Number of vertices that will be drawn. */
inline GLuint Shape::getLimit() const {return limit;}

/** @return User-assigned name of the shape. */
inline string Shape::getName() const {return name;}

/** @return Program the shape sends vertex attributes to. */
inline Program* Shape::getProgram() const {return program;}

/** Set attributes in use for this shape. */
inline void Shape::setAttributes(list<VertexAttribute> &a) {attributes = a;}

/** Sets the number of vertices in the shape. */
inline void Shape::setCount(GLuint c) {count = c;}

/** Sets the number of vertices that will be drawn. */
inline void Shape::setLimit(GLuint l) {limit = l;}

/** Sets the program to send vertex attributes to. */
inline void Shape::setProgram(Program *p) {program = p;}

#endif

