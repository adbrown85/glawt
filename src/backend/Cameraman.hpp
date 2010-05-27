/*
 * Cameraman.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CAMERAMAN_HPP
#define CAMERAMAN_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include "Command.hpp"
#include "Worker.hpp"
using namespace std;


/** @brief Worker responsible for moving or rotating the camera.
 * @ingroup backend
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

