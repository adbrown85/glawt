/*
 * VertexBufferObject.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP
#include "BufferObject.hpp"
#include "VertexAttribute.hpp"
#include "Exception.hpp"
using namespace std;


/** @brief OpenGL buffer object for vertex attributes.
 * 
 * To use, create a new VertexBufferObject.  Before adding values, reserve 
 * space for the VBO using allocate().  Then use the variations of put() to 
 * fill the buffer.  Finally, call flush() to send the data to the card.
 * 
 * To update data, call rewind() to go back to the beginning of the buffer and
 * then call the put() methods again to overwrite the data in the buffer.  
 * Remember to call flush() when you are done.
 * 
 * Lastly, if you would like to update just one attribute, call 
 * enableStriding() before making any calls to put.  
 * 
 * @ingroup graphics
 */
class VertexBufferObject: public BufferObject {
public:
	VertexBufferObject();
	virtual ~VertexBufferObject();
// Primary interface
	void allocate(GLenum usage, GLuint count, list<VertexAttribute> &attribs);
	void put(float x, float y);
	void put(float x, float y, float z);
	void put(float x, float y, float z, float w);
	void flush();
// Secondary interface
	void enableStriding();
	void disableStriding();
	void rewind();
	void seek(const string &name);
// Getters and setters
	bool isAllocated() const;
	bool isInterleaved() const;
	void setInterleaved(bool interleaved);
	GLsizei getSize() const;
private:
	static int SIZEOF_VEC2, SIZEOF_VEC3, SIZEOF_VEC4;
	bool interleaved;
	GLubyte *data, *current, *end;
	GLuint count, stride;
	GLsizei size;
	map<string,GLuint> positions;
};

/** @return Size in bytes of the VBO. */
inline GLsizei VertexBufferObject::getSize() const {return size;}

/** @return True if the VBO has been allocated. */
inline bool VertexBufferObject::isAllocated() const {return end != data;}

/** @return True if this VBO keeps all attributes of a vertex together. */
inline bool VertexBufferObject::isInterleaved() const {return interleaved;}

#endif
