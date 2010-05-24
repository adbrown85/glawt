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
using namespace std;


/**
 * @ingroup backend
 * @brief %Delegate responsible for moving or rotating the camera.
 */
class Cameraman : public Delegate {
public:
	Cameraman();
	static void fit(Scene *scene, Canvas *canvas, int command);
	static void reset(Scene *scene, Canvas *canvas, int command);
	static void rotate(Scene *s, Canvas *c, int command, float amount);
	static void translate(Scene *s, Canvas *c, int command, float amount);
};


#endif

