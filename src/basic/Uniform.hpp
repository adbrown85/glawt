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
#include "Program.hpp"
#include "Tag.hpp"
#include "Text.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
using namespace std;


/** @brief Abstract base class for GLSL uniform variables.
 * @ingroup basic
 */
class Uniform : public Applicable, public Suppressable {
public:
	Uniform(const Tag &tag);
	virtual void associate();
	virtual void apply() = 0;
	virtual void finalize();
	GLint getLocation() const;
	string getName() const;
	Program* getProgram() const;
	virtual void remove() {};
	void setLocation(GLint location);
	void setName(const string &name);
	void setProgram(Program *program);
	virtual string toString() const;
	virtual bool wasSuppressed() const;
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
