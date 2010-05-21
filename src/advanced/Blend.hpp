/*
 * Blend.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BLEND_HPP
#define BLEND_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <GL/glut.h>
#include "Node.hpp"
#include "Tag.hpp"
#include "Translate.hpp"
#include "Window.hpp"
using namespace std;


/** @brief Mixes colors together based on their alpha value.
 * @ingroup advanced
 */
class Blend : public Applicable {
public:
	Blend(const Tag &tag) : Applicable(tag) {}
	virtual void apply();
	virtual void remove();
protected:
	void sortChildren();
private:
	list<Translate*> translates;
};


#endif
