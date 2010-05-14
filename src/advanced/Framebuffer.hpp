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
#include <list>                         // Storing attachments
#include "Applicable.hpp"
#include "Attachable.hpp"
#include "Texture2D.hpp"


/* Group of similar framebuffer attachments. */
struct Chain {
	Chain() {}
	Chain(GLenum base, GLuint max) : base(base), max(max) {}
	GLenum base;                        // GL_COLOR_ATTACHMENT0, etc.
	GLuint max;                         // Maximum amount of items
	list<Attachable*> attachables;      // Attached items
};


/**
 * @ingroup advanced
 * @brief Container for offscreen rendering targets.
 * 
 * Replaces the default framebuffer with an external framebuffer object 
 * comprised of a number of attachments.  When the framebuffer is active, 
 * rendering will be redirected to these attachments instead of the screen.  
 * Thus framebuffer can be used to render in multiple passes or to perform 
 * general-purpose computations.
 * 
 * %Framebuffer cannot be used by itself.  Make sure to place one or more 
 * Attachment nodes under the framebuffer.
 * 
 * <b>XML Name</b>
 *   - framebuffer
 * 
 * <b>XML Example</b>
 * <pre>
 *   &lt;framebuffer>
 *     &lt;attachment />
 *     &lt;attachment />
 *   &lt;/framebuffer>
 * </pre>
 * 
 * @see Attachment
 * @see Target
 */
class Framebuffer : public Applicable {
public:
	Framebuffer(const Tag &tag);
	virtual ~Framebuffer();
	virtual bool areChildrenSelectable();
	virtual void attach(const string &type, Attachable *item);
	virtual void apply();
	static Framebuffer* find(Node *node);
	virtual GLuint getHandle() const;
	static bool isActive();
	virtual void remove();
	virtual void verify();
	virtual string toString() const;
protected:
	virtual void activate();
	virtual void associate();
	virtual void attach();
	virtual void attach(Chain &chain);
	virtual void finalize();
	virtual Chain* getChain(const string &name);
	static GLint getMaxDrawBuffers();
	static GLint getMaxColorAttachments();
private:
	static bool active;
	GLuint handle;
	map<string,Chain> chains;
};

/** Disables trying to pick children drawn into a framebuffer. */
inline bool Framebuffer::areChildrenSelectable() {return false;}

/** @return Integer identifying the underlying OpenGL framebuffer object. */
inline GLuint Framebuffer::getHandle() const {return handle;}

/** @return True if a Framebuffer is active. */
inline bool Framebuffer::isActive() {return active;}


#endif
