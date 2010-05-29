/*
 * Grip.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GRIP_HPP
#define GRIP_HPP
#include "common.h"
#include "Worker.hpp"                   // Base class
#include "Scale.hpp"
#include "Translate.hpp"
using namespace std;


/** @brief Responsible for moving individual items around the scene.
 * @ingroup command
 */
class Grip : public Worker {
public:
	Grip(Scene *s, Canvas *c) : Worker(s,c) {}
	void rotate(int cmd, float argument);
	void scale(int cmd, float argument);
	void translate(int cmd, float argument);
};


#endif
