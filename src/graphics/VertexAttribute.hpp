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
	GLint getLocation() const;
	string getName() const;
	void setComponents(GLuint components);
	void setName(string name);
	void setLocation(GLint location);
private:
	string name;
	GLint location;
	GLuint components;
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

#endif
