/*
 * Outputs.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OUTPUTS_HPP
#define OUTPUTS_HPP
#include "common.h"
#include <algorithm>                    // Finding attachments
#include "Attachment.hpp"
using namespace std;


/** @brief Activates framebuffer attachments.
 * @ingroup advanced
 */
class Outputs : public Node, public Applicable {
public:
	Outputs(const Tag &tag);
	~Outputs();
	virtual GLint addAttachment(Attachment *attachment);
	virtual void apply();
	static Outputs* find(Node *node);
	static GLuint getMaxDrawBuffers();
	virtual void remove() {}
	virtual string toString() const;
protected:
	virtual void associate();
	virtual void finalize();
private:
	list<Attachment*> attachments;
	Framebuffer *framebuffer;
	GLenum *locations;
	GLsizei n;
};


#endif
