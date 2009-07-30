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
using std::cerr;
using std::endl;
using std::vector;



class Program : public Node,
                public Applicable {
	
	
	public :
		
		Program();
		void apply();
		void associate();
		void finalize();
		GLuint getName() const {return name;}
		void remove();
	
	
	private:
		
		GLuint name;
		
		void log() const;
};


#endif
