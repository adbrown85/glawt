/*
 * Director.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include "common.h"
#include "Worker.hpp"                   // Base class
using namespace std;


/** @brief %Worker responsible for selecting items in the scene.
 * @ingroup backend
 */
class Director : public Worker {
public:
	Director(Scene *s, Canvas *c) : Worker(s,c) {}
	void grab(int cmd, float id);
	void iterate(int cmd);
	void select(int cmd);
};


#endif
