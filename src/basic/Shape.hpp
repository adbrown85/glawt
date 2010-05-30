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
#include "NodeEvent.hpp"
#include "Transformation.hpp"
#include "Transform.hpp"
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
 * @ingroup basic
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
 */
class Shape : public SimpleDrawable,
              public NodeListener {
public:
	Shape(const Tag &tag, ShapeTraits traits);
	virtual void associate();
	virtual void draw() const;
	void draw(int first, int number) const;
	virtual void finalize();
	virtual list<VertexAttribute> getAttributes() const;
	virtual GLuint getCount() const;
	virtual string getName() const;
	virtual Vector getPosition() const;
	virtual Program* getProgram() const;
	virtual void onNodeEvent(NodeEvent &event);
	virtual void setAttributes(list<VertexAttribute> &attributes);
	virtual void setProgram(Program *program);
	virtual string toString() const;
protected:
	virtual GLuint getOffset(const string &name) const;
	static bool isBufferStored(const string &className);
	void setBufferData(const string &name, GLfloat data[][3]);
	virtual void setCount(GLuint count);
	virtual void updateBuffer() = 0;
	virtual void updatePosition();
private:
	list<VertexAttribute> attributes;
	GLenum mode, usage;
	GLuint block, buffer, count;
	static map<string,GLuint> buffers;
	map<string,GLuint> offsets;
	Program *program;
	string name;
	Vector position;
	list<Transformation*> transforms;
};

/** @return Attributes in use for this shape. */
inline list<VertexAttribute> Shape::getAttributes() const {return attributes;}

/** @return Number of vertices in the shape. */
inline GLuint Shape::getCount() const {return count;}

/** @return User-assigned name of the shape. */
inline string Shape::getName() const {return name;}

/** @return Position of the item in the scene. */
inline Vector Shape::getPosition() const {return position;}

/** @return Program the shape sends vertex attributes to. */
inline Program* Shape::getProgram() const {return program;}

/** Updates the position when a transform changes. */
inline void Shape::onNodeEvent(NodeEvent &event) {updatePosition();}

/** Set attributes in use for this shape. */
inline void Shape::setAttributes(list<VertexAttribute> &a) {attributes = a;}

/** Sets the number of vertices in the shape. */
inline void Shape::setCount(GLuint c) {count = c;}

/** Sets the program to send vertex attributes to. */
inline void Shape::setProgram(Program *p) {program = p;}

#endif

