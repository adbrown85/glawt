/*
 * Screen.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCREEN_HPP
#define SCREEN_HPP
#include "common.h"
#include "Framebuffer.hpp"
using namespace std;


/** @brief Temporarily disables a framebuffer in order to render to the screen.
 * 
 * <b>XML name</b>
 *   - <i>screen</i>
 * 
 * <b>OpenGL functions</b>
 *   - <i>glBindFramebuffer</i>
 * 
 * @ingroup advanced
 * @see Framebuffer
 */
class Screen : public Node, public Applicable {
public:
	Screen(const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual void remove();
private:
	Framebuffer *framebuffer;
};


#endif
