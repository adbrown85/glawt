/*
 * Sort.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SORT_HPP
#define SORT_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>                    // For sort
#include <list>                         // For storing translate nodes
#include "Node.hpp"
#include "Translate.hpp"
#include "Window.hpp"
using namespace std;


/** @brief Sorts translate children based on their depth.
 * @ingroup advanced
 */
class Sort : public Applicable {
public:
	Sort(const Tag &tag) : Applicable(tag) {}
	virtual void apply();
	virtual void associate();
	virtual void remove() {}
private:
	list<Translate*> translates;
	Matrix rotation;
	Vector position;
};


#endif
