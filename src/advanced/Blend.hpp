/*
 * Blend.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BLEND_HPP
#define BLEND_HPP
#include "common.h"
#include <algorithm>
#include "Node.hpp"
#include "Tag.hpp"
#include "Translate.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief Mixes colors together based on their alpha value.
 * @ingroup advanced
 */
class Blend : public Node, public Applicable {
public:
	Blend(const Tag &tag) : Node(tag) {}
	virtual void apply();
	virtual void remove();
private:
	list<Translate*> translates;
};


#endif
