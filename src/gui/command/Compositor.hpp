/*
 * Compositor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMPOSITOR_HPP
#define COMPOSITOR_HPP
#include "common.h"
#include "Worker.hpp"
using namespace std;


/** @brief Responsible for hiding and showing items.
 * @ingroup command
 */
class Compositor : public Worker {
public:
	Compositor(Scene *s, Canvas *c) : Worker(s,c) {}
	void hide(int command);
	void showAll(int command);
};


#endif
