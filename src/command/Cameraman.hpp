/*
 * Cameraman.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CAMERAMAN_HPP
#define CAMERAMAN_HPP
#include "common.h"
#include "Worker.hpp"                   // Base class
using namespace std;


/** @brief Responsible for moving or rotating the camera.
 * @ingroup command
 */
class Cameraman : public Worker {
public:
	Cameraman(Scene *s, Canvas *c) : Worker(s,c) {}
	void fit(int command);
	void reset(int command);
	void rotate(int command, float amount);
	void translate(int command, float amount);
};


#endif

