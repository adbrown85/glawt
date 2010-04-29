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
#include "Tag.hpp"


/**
 * @ingroup advanced
 * @brief
 *     Container for offscreen rendering targets.
 */
class Framebuffer : public Node,
                    public Applicable {
	
	public :
		
		Framebuffer();
		Framebuffer(const Tag &tag);
		~Framebuffer();
		virtual void apply();
		virtual GLuint getHandle() const;
		virtual void remove();
		virtual string toString() const;
		
		static void find(Node *node,
		                 Framebuffer *&pointer);
		static bool isActive();
	
	protected:
		
		virtual void associate();
	
	private:
		
		GLuint depthBuffer, handle;
		
		static bool active;
};


/**
 * @return true if a Framebuffer is active.
 */
inline bool Framebuffer::isActive() {return active;}


/**
 * @return integer identifying the framebuffer with OpenGL.
 */
inline GLuint Framebuffer::getHandle() const {return handle;}


#endif
