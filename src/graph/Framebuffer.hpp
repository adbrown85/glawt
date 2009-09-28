/*
 * Framebuffer.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Applicable.hpp"
#include "Node.hpp"



class Framebuffer : public Node,
                    public Applicable {
	
	
	public :
		
		Framebuffer();
		~Framebuffer();
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
		
		virtual GLuint getHandle() {return handle;}
		
		static void find(Node *node,
		                 Framebuffer *&pointer);
	
	
	protected:
		
		virtual void associate();
	
	
	private:
		
		GLuint depthBuffer, handle;
};


#endif
