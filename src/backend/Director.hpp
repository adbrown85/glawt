/*
 * Director.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
using namespace std;


/** @brief %Worker responsible for selecting items in the scene.
 * @ingroup backend
 */
class Director {
public:
	Director(Scene *scene, Canvas *canvas);
	void grab(int cmd, float id);
	void iterate(int cmd);
	void select(int cmd);
private:
	Canvas *canvas;
	Scene *scene;
};


#endif
