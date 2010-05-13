/*
 * Target.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TARGET_HPP
#define TARGET_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Attachment.hpp"               // Base class
#include "Texture2D.hpp"                // Backer
using namespace std;


/**
 * @ingroup advanced
 * @brief Offscreen render location backed by a texture.
 * 
 * <b>XML Name</b>
 *   - target
 * 
 * <b>XML Attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>link</i></td>
 *   <td>Name of the texture that backs the render target.</td>
 * </tr>
 * </table>
 * 
 * <b>XML Example</b>
 * <pre>
 *   &lt;texture name="mytexture" >
 *     &lt;framebuffer>
 *       &lt;target link="mytexture" />
 *     &lt;/framebuffer>
 *   &lt;/texture>
 * </pre>
 * 
 * <b>Notes</b>
 *   - Target's name is a copy of the <i>link</i> attribute.
 */
class Target : public Attachment {
public:
	Target(const Tag &tag);
	virtual void attach();
	virtual int getSize() const;
	string toString() const;
protected:
	void associate();
private:
	Texture2D *texture;
	string link;
};

/** @return width of the texture backing the render target. */
inline int Target::getSize() const {return texture->getSize();}


#endif
