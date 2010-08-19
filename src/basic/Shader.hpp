/*
 * Shader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADER_HPP
#define SHADER_HPP
#include "common.h"
#include <cstring>
#include <fstream>
#include <vector>
#include "Error.hpp"
#include "Node.hpp"
#include "Program.hpp"
#include "Preprocessor.hpp"
#include "Tag.hpp"
#include "Scout.hpp"
using namespace std;


/** @brief GLSL shader with loading and compiling capabilities.
 * @ingroup basic
 */
class Shader : public Node {
public:
	Shader(const Tag &tag);
	~Shader();
	void associate();
	void finalize() {}
	string getFilename() const {return filename;}
	GLuint getHandle() const {return handle;}
	string getType() const {return type;}
	void list() const;
	void log() const;
	string toString() const;
protected:
	void compile();
	void create();
	void load();
private:
	const char **source;
	GLuint handle;
	int length;
	Preprocessor preprocessor;
	string filename, type;
};


#endif
