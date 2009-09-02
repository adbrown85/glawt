/*
 * Program.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Applicable.hpp"
#include "Node.hpp"
using namespace std;



/**
 * @brief
 *     GLSL program that %Shaders and %Uniform variables are connected to.
 * @ingroup graph
 */
class Program : public Node,
                public Applicable {
	
	
	public :
		
		Program();
		void apply();
		void associate();
		void finalize();
		void remove();
		
		GLuint getName() const {return name;}
		static Program* getCurrent() {return current;}
	
	
	private:
		
		GLuint name;
		
		static Program *current;
		
		void log() const;
};


#endif
