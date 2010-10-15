/*
 * Renderbuffer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP
#include "common.h"
#include "Attachment.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief Offscreen render location that can be attached to a %Framebuffer.
 * 
 * Convenient if the Framebuffer object needs a depth buffer, or if the user 
 * needs to render to an offscreen location but does not want to use that data 
 * as a texture.  (In that case use Target.)
 * 
 * It should be possible to use <i>glReadPixels</i> with the renderbuffer.  
 * Use getHandle() to retrieve the underlying OpenGL renderbuffer object.
 * 
 * <b>XML Name</b>
 *   - renderbuffer
 * 
 * <b>XML Attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>type</i></td>
 *   <td><i>color</i> or <i>depth</i></td>
 * </tr>
 * <tr>
 *   <td><i>size</i></td>
 *   <td>Width and height of the renderbuffer storage.</td>
 * </tr>
 * </table>
 * 
 * <b>OpenGL Functions</b>
 *   - glGenRenderbuffers
 *   - glDeleteRenderbuffers
 *   - glBindRenderbuffer
 *   - glRenderbufferStorage
 *   - glFramebufferRenderbuffer
 * 
 * <b>Example</b>
 * <pre>
 *   &lt;framebuffer>
 *     &lt;renderbuffer type="depth" size="512" />
 *     &lt;clear />
 *   &lt;/framebuffer>
 * </pre>
 * 
 * @note Remember to use Clear if using a depth renderbuffer.
 * 
 * @ingroup advanced
 * @see Framebuffer
 * @see Target
 * @see Clear
 */
class Renderbuffer : public Attachment {
public:
	Renderbuffer(const Tag &tag);
	~Renderbuffer();
	virtual void associate();
	virtual void attach();
	virtual GLuint getHandle() const;
	virtual Vector read(int x, int y) const;
	virtual string toString() const;
protected:
	void setFormat(GLenum format);
private:
	GLenum format;
	GLuint handle;
	int size;
};

/** @return Integer identifying the underlying OpenGL renderbuffer object. */
inline GLuint Renderbuffer::getHandle() const {return handle;}

inline void Renderbuffer::setFormat(GLenum format) {this->format = format;}


#endif
