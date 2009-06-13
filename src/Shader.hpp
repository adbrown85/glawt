/*
 * Shader.hpp
 *     Handles loading and installing GLSL shaders.
 * 
 * Author
 *     Andy Brown <adb1413@rit.edu>
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



class Shader {
	
	
	public :
		
		Shader(GLenum type);
		~Shader();
		
		static void add(Uniform uniform);
		void compile();
		std::string getFilename();
		static void link();
		void load(std::string filename);
		void print() const;
		static void setUniform(std::string name,
		                       int type,
		                       GLfloat value);
		static void setUniform(const Uniform& uniform);
	
	
	private :
		
		const char **source;
		GLenum type;
		GLuint name;
		int count;
		static GLuint program;
		static std::vector<Uniform> uniforms;
		std::string filename;
		std::vector<std::string> lines;
		
		static void log(GLuint name);
};


#endif
