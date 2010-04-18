/*
 * Shader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADER_HPP
#define SHADER_HPP
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Node.hpp"
#include "Program.hpp"
#include "Preprocessor.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     GLSL shader with loading and compiling capabilities.
 */
class Shader : public Node {
	
	public :
		
		Shader(string type,
		       string filename);
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
	
	private :
		
		const char **source;
		GLuint handle;
		int length;
		Preprocessor preprocessor;
		string filename, type;
		
		Shader();
		void compile();
		void create();
		int findLogLine(const string &line) const;
		void init();
		void initType();
		void load();
};


#endif
