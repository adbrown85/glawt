/*
 * Program.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <GL/glut.h>
#include "Node.hpp"
#include "Log.hpp"
#include "Preprocessor.hpp"
#include "NodeEvent.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief GLSL program that %Shaders and %Uniform variables are connected to.
 */
class Program : public Applicable {
public:
	Program(const Tag& tag);
	virtual void addCode(int handle, const Preprocessor *preprocessor);
	virtual void addListener(NodeListener *listener, int type);
	virtual void apply();
	virtual void associate();
	virtual void finalize();
	static Program* find(Node* node);
	static Program* getCurrent();
	virtual GLuint getHandle() const;
	virtual void log() const;
	virtual void remove();
	virtual string toString() const;
private:
	GLuint handle;
	map<int,const Preprocessor*> code;
	static Program* current;
	NodeNotifier notifier;
	Program *previous;
};

/** @return Integer OpenGL identifies the program with. */
inline GLuint Program::getHandle() const {return handle;}

/** @return Pointer to the active program */
inline Program* Program::getCurrent() {return current;}


#endif
