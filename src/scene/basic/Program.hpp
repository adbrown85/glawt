/*
 * Program.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "common.h"
#include <cstring>
#include <vector>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Error.hpp"
#include "Code.hpp"
#include "NodeEvent.hpp"
#include "Scout.hpp"
using namespace std;


/** @brief GLSL program that %Shaders and %Uniform variables are connected to.
 * @ingroup basic
 */
class Program : public Node, public Applicable {
public:
	Program(const Tag& tag);
	virtual void addListener(NodeListener *listener, int type);
	virtual void apply();
	virtual void associate();
	virtual void finalize();
	static Program* getCurrent();
	virtual GLuint getHandle() const;
	virtual void log() const;
	virtual void remove();
	virtual string toString() const;
private:
	GLint linked;
	GLuint handle;
	static Program* current;
	NodeNotifier notifier;
	Program *previous;
};

/** @return Integer OpenGL identifies the program with. */
inline GLuint Program::getHandle() const {return handle;}

/** @return Pointer to the active program */
inline Program* Program::getCurrent() {return current;}


#endif
