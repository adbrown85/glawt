/*
 * VertexAttribute.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef VERTEXATTRIBUTE_HPP
#define VERTEXATTRIBUTE_HPP
#include "common.h"
using namespace std;


/** @brief Value for a vertex.
 * 
 * @ingroup graphics
 */
class VertexAttribute {
public:
	VertexAttribute();
	VertexAttribute(const string &name, GLuint components);
	virtual ~VertexAttribute();
public:
	GLuint getComponents() const;
	void setComponents(GLuint components);
	GLint getLocation() const;
	void setLocation(GLint location);
	string getName() const;
	void setName(string name);
	GLint getNumber() const;
	void setNumber(GLint number);
	GLuint getOffset() const;
	void setOffset(GLuint offset);
private:
	string name;
	GLint location;
	GLuint components;
	GLint number; // SHOULD REMOVE THIS
	GLuint offset; // SHOULD REMOVE THIS
};

/** @return Number of components in the attribute. */
inline GLuint VertexAttribute::getComponents() const {return components;}
inline void VertexAttribute::setComponents(GLuint c) {this->components = c;}

/** @return Location of the attribute in the shader program. */
inline GLint VertexAttribute::getLocation() const {return location;}
inline void VertexAttribute::setLocation(GLint l) {this->location = l;}

/** @return Name of the attribute. */
inline string VertexAttribute::getName() const {return name;}
inline void VertexAttribute::setName(string name) {this->name = name;}

/** @return Number of the attribute. */
inline GLint VertexAttribute::getNumber() const {return number;}
inline void VertexAttribute::setNumber(GLint number) {this->number = number;}

/** @return Location of the attribute. */
inline GLuint VertexAttribute::getOffset() const {return offset;}
inline void VertexAttribute::setOffset(GLuint offset) {this->offset = offset;}

#endif
