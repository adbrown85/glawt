/*
 * Wireframe.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP
#include "common.h"
#include "Node.hpp"
using namespace std;


/** @brief Causes only the edges of shapes to be drawn.
 * @ingroup basic
 */
class Wireframe : public Node, public Applicable {
public:
	Wireframe(const Tag &tag);
	virtual void apply();
	virtual void remove();
	virtual string toString() const;
private:
	GLenum mode;
	string faces;
};


#endif
