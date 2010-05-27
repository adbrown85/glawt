/*
 * Compositor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMPOSITOR_HPP
#define COMPOSITOR_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <queue>                        // For showing all
#include "Command.hpp"
#include "Worker.hpp"
using namespace std;


/** @brief Worker responsible for hiding and showing items.
 * @ingroup backend
 */
class Compositor : public Worker {
public:
	Compositor(Scene *s, Canvas *c) : Worker(s,c) {}
	void hide(int command);
	void showAll(int command);
};


#endif
