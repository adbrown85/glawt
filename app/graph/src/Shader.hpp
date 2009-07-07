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
#include <string>
#include <vector>
#include "Uniform.hpp"
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;



/**
 * @brief
 *     GLSL shader with loading, compiling, and installing capabilities.
 * @ingroup graph
 */
class Shader {
	
	
	public :
		
		Shader(GLenum type);
		~Shader();
		
		static void add(Uniform uniform);
		void compile();
		string getFilename();
		static void link();
		void load(string filename);
		void print() const;
		static void setUniform(string name,
		                       int type,
		                       GLfloat value);
		static void setUniform(const Uniform& uniform);
	
	
	private :
		
		const char **source;
		GLenum type;
		GLuint name;
		int count;
		static GLuint program;
		static vector<Uniform> uniforms;
		string filename;
		vector<string> lines;
		
		static void log(GLuint name);
};


#endif
