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
#include "Node.hpp"
#include "Program.hpp"
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;



/**
 * @brief
 *     GLSL shader with loading and compiling capabilities.
 * @ingroup graph
 */
class Shader : public Node {
	
	
	public :
		
		Shader();
		~Shader();
		void associate();
		void compile();
		void finalize() {}
		void load(char type,
		          string filename);
		void log() const;
		void print() const;
		
		GLuint getName() const {return name;}
		string getFilename() const {return filename;}
		char getType() const {return type;}
	
	
	private :
		
		char type;
		const char **source;
		GLuint name;
		int length;
		string filename;
		vector<string> lines;
		
		void clear();
		void create();
		void open();
};


#endif
