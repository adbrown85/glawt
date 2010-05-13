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
#include "Texture2D.hpp"


/* Item that can be attached to the framebuffer. */
class Attachable {
public:
	virtual void attach() = 0;
	virtual void setLocation(GLuint location) = 0;
	virtual void setIndex(GLint index) = 0;
};


/* Slot in the framebuffer items can be attached to. */
struct FramebufferSlot {
	GLenum base;                        // GL_COLOR_ATTACHMENT0, etc.
	GLuint maximum;                     // Maximum amount of items
	list<Attachable*> attachables;      // Attached items
};


/**
 * @ingroup advanced
 * @brief Container for offscreen rendering targets.
 */
class Framebuffer : public Applicable {
public:
	Framebuffer(const Tag &tag);
	~Framebuffer();
	virtual bool areChildrenSelectable();
	virtual void add(const string &type, Attachable *attachable);
	virtual void apply();
	static Framebuffer* find(Node *node);
	virtual GLuint getHandle() const;
	static bool isActive();
	virtual void remove();
	virtual string toString() const;
protected:
	virtual void associate();
	virtual void finalize();
	virtual FramebufferSlot* getSlot(const string &name);
private:
	static bool active;
	GLuint handle;
	map<string,FramebufferSlot> slots;
};

/** Disables trying to pick children drawn into a framebuffer. */
inline bool Framebuffer::areChildrenSelectable() {return false;}

/** @return integer identifying the framebuffer with OpenGL. */
inline GLuint Framebuffer::getHandle() const {return handle;}

/** @return true if a Framebuffer is active. */
inline bool Framebuffer::isActive() {return active;}


#endif
