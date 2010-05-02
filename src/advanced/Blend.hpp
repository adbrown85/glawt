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
#include "Applicable.hpp"
#include "Tag.hpp"
#include "Translation.hpp"
#include "Window.hpp"
using namespace std;


class Blend : public Applicable {
public:
	Blend(const Tag &tag);
	virtual void apply();
	virtual void associate();
	//virtual list<Node*> getChildren() const;
	virtual void remove();
protected:
	void sortChildren();
private:
	list<Translation*> translates;
};


#endif
