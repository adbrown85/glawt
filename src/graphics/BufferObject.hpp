/*
 * BufferObject.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP
#include "common.h"
using namespace std;

/** @brief OpenGL buffer object.
 * 
 * @ingroup graphics
 */
class BufferObject {
public:
	BufferObject(GLenum type);
	virtual ~BufferObject();
	virtual void bind();
	virtual void unbind();
protected:
	virtual void allocate(GLenum usage, GLsizei size);
	virtual void update(GLsizei size, GLvoid *data, int offset=0);
public:
	virtual GLuint getHandle() const;
	virtual GLenum getType() const;
private:
	GLuint handle;
	GLenum type;
};

/** @return OpenGL's underlying identifier for the buffer. */
inline GLuint BufferObject::getHandle() const {return handle;}

/** @return Type of the buffer. */
inline GLenum BufferObject::getType() const {return type;}

#endif
