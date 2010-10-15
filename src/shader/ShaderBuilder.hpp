/*
 * ShaderBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADERBUILDER_HPP
#define SHADERBUILDER_HPP
#include "common.h"
#include "Preprocessor.hpp"
#include "Error.hpp"
using namespace std;


/** @brief Creates, loads, and compiles a shader.
 * @ingroup basic
 */
class ShaderBuilder {
public:
	void build(const string &type, const string &filename);
public:    // Accessors
	GLuint getHandle() const;
protected: // Helpers
	void compile();
	void create();
	void load();
private:   // Data
	string filename, type;
	GLuint handle;
	Code code;
};

inline GLuint ShaderBuilder::getHandle() const {return handle;}


#endif
