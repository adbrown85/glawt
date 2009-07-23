/*
 * Program.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Shader.hpp"
using std::vector;



class Program {
	
	
	public :
		
		Program();
		void add(Shader *shader);
		GLuint getName() const {return name;}
		void install();
	
	
	private:
		
		GLuint name;
		vector<Shader*> shaders;
		
		void compile();
		void link();
};


#endif
