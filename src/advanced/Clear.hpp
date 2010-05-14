/*
 * Clear.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CLEAR_HPP
#define CLEAR_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/gl.h>
#include "Applicable.hpp"               // Base class
using namespace std;


/**
 * @ingroup advanced
 * @brief Clear a framebuffer.
 * 
 * Although actually one of the most mundane operations, most of the time clear 
 * is not directly needed by the user because the display loop will it do 
 * automatically.  However, when working with framebuffer objects, it does 
 * sometimes become necessary when doing multiple passes.
 */
class Clear : public Applicable {
public:
	Clear(const Tag &tag);
	virtual void apply();
	virtual void remove() {}
	virtual string toString() const;
private:
	float r, g, b;
};


#endif
