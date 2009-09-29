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
#include "Tag.hpp"
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
		Program(const Tag &tag);
		virtual void apply();
		virtual void associate();
		virtual void finalize();
		virtual void remove();
		virtual string toString() const;
		
		virtual GLuint getHandle() const {return handle;}
		
		static Program* getCurrent() {return current;}
	
	
	private:
		
		GLuint handle;
		
		static Program *current;
		
		void log() const;
};


#endif
