/*
 * Shader.hpp
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
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
using namespace std;



/**
 * @brief
 *     GLSL shader with loading and compiling capabilities.
 * @ingroup graph
 */
class Shader : public Node {
	
	
	public :
		
		Shader(string type,
		       string filename);
		~Shader();
		void associate();
		void finalize() {}
		void list() const;
		void log() const;
		string toString() const;
		
		GLuint getName() const {return name;}
		string getFilename() const {return filename;}
		string getType() const {return type;}
	
	
	private :
		
		const char **source;
		GLuint name;
		int length;
		string filename, type;
		vector<string> lines;
		
		Shader();
		void compile();
		void create();
		void load();
};


#endif
