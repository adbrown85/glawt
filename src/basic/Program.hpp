/*
 * Program.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Applicable.hpp"
#include "Log.hpp"
#include "Node.hpp"
#include "Preprocessor.hpp"
#include "Tag.hpp"
#define POINT_LOCATION 0
#define POINT_NAME "MCVertex"
#define NORMAL_LOCATION 1
#define NORMAL_NAME "MCNormal"
#define COORD_LOCATION 2
#define COORD_NAME "TexCoord0"
using namespace std;


/**
 * @ingroup basic
 * @brief GLSL program that %Shaders and %Uniform variables are connected to.
 */
class Program : public Applicable {
public:
	Program(const Tag& tag);
	virtual void addCode(int handle, const Preprocessor *preprocessor);
	virtual void apply();
	virtual void associate();
	virtual void finalize();
	static Program* find(Node* node);
	GLint getAttributeLocation(const string &name);
	static Program* getCurrent();
	virtual GLuint getHandle() const;
	void setAttributeLocation(GLuint index, const string &name);
	virtual void log() const;
	virtual void remove();
	virtual string toString() const;
private:
	GLuint handle;
	map<int,const Preprocessor*> code;
	static Program* current;
};


inline GLuint Program::getHandle() const {
	return handle;
}

inline Program* Program::getCurrent() {
	return current;
}


#endif
