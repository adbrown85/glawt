/*
 * Outputs.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OUTPUTS_HPP
#define OUTPUTS_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <list>                         // Storing attachments
#include <algorithm>                    // Finding attachments
#include "Attachment.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Activates framebuffer attachments.
 */
class Outputs : public Applicable {
public:
	Outputs(const Tag &tag);
	~Outputs();
	virtual GLint addAttachment(Attachment *attachment);
	virtual void apply();
	static Outputs* find(Node *node);
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
