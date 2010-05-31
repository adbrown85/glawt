/*
 * Attachment.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ATTACHMENT_HPP
#define ATTACHMENT_HPP
#include "common.h"
#include "Node.hpp"                     // Base class
#include "Framebuffer.hpp"              // Attach to framebuffer
using namespace std;


/** @brief Abstract base class for an item attached to the framebuffer.
 * @ingroup advanced
 */
class Attachment : public Attachable {
public:
	Attachment(const Tag &tag, const string &type);
	virtual void attach() = 0;
	static Attachment* find(Node *node, const string &name);
	Framebuffer* getFramebuffer() const;
	GLint getIndex() const;
	GLuint getLocation() const;
	virtual string getName() const;
	virtual void setIndex(GLint index);
	virtual void setLocation(GLuint location);
	virtual string toString() const;
protected:
	virtual void associate();
	virtual void setName(const string &name);
	virtual void setType(const string &type);
private:
	Framebuffer *framebuffer;
	GLint index;
	GLuint location;
	string name, type;
};

/** @return %Framebuffer item attaches to. */
inline Framebuffer* Attachment::getFramebuffer() const {return framebuffer;}

/** @return Index in the framebuffer item attached to. */
inline GLint Attachment::getIndex() const {return index;}

/** @return Location in the framebuffer item attached to. */
inline GLuint Attachment::getLocation() const {return location;}

/** @return User-defined name identify the attachment. */
inline string Attachment::getName() const {return name;}

/** Sets the location the attachment should be attached to. */
inline void Attachment::setLocation(GLuint loc) {this->location = loc;}

/** Sets the user-defined name of the attachment. */
inline void Attachment::setIndex(GLint index) {this->index = index;}

/** Sets the user-defined name of the attachment. */
inline void Attachment::setName(const string &name) {this->name = name;}

/** Sets the user-defined name of the attachment. */
inline void Attachment::setType(const string &t) {type = t;}


#endif
