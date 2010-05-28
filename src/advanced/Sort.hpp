/*
 * Sort.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SORT_HPP
#define SORT_HPP
#include "common.h"
#include <algorithm>                    // For sort
#include <list>                         // For storing translate nodes
#include "Node.hpp"
#include "Translate.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief Sorts translate children based on their depth.
 * @ingroup advanced
 */
class Sort : public Applicable, public Dependent {
public:
	Sort(const Tag &tag) : Applicable(tag) {}
	virtual void apply();
	virtual void associate();
	virtual void remove() {}
	virtual void setCanvas(Canvas *canvas);
private:
	Canvas *canvas;
	list<Translate*> translates;
	Matrix rotation;
	Vector position;
};

/** Sets the canvas to calculate the depth with. */
inline void Sort::setCanvas(Canvas *c) {canvas = c;}


#endif
