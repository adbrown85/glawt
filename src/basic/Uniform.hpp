/*
 * Uniform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include "common.h"
#include <iomanip>
#include <set>
#include "Matrix.hpp"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Program.hpp"
#include "Tag.hpp"
#include "Text.hpp"
#include "Texture.hpp"
using namespace std;

/* Information about a uniform. */
struct UniformInfo {
	GLenum type;
	GLint count;
};

/** @brief Abstract base class for GLSL uniform variables.
 * @ingroup basic
 */
class Uniform : public Node,
                public Applicable, public Suppressable {
public: // Core
	Uniform(const Tag &tag);
	virtual void associate();
	virtual void apply() = 0;
	virtual void finalize();
	virtual void remove() {};
	virtual string toString() const;
	virtual bool wasSuppressed() const;
public: // Accessors and mutators
	GLint getLocation() const;
	string getName() const;
	Program* getProgram() const;
	void setLocation(GLint location);
	void setName(const string &name);
	void setProgram(Program *program);
public: // Utilities
	static map<string,UniformInfo> getUniformsFor(Program *program);
	static string getTypeNameFor(GLenum type);
	static bool isMatrixType(GLenum type);
protected:
	GLint location;
	Program *program;
	string link, name, type;
};


inline GLint Uniform::getLocation() const {return location;}
inline string Uniform::getName() const {return name;}
inline Program* Uniform::getProgram() const {return program;}
inline void Uniform::setLocation(GLint location) {this->location = location;}
inline void Uniform::setName(const string &n) {name = n;}
inline void Uniform::setProgram(Program *program) {this->program = program;}


#endif
