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
#include "Command.hpp"
using namespace std;


/** @brief Worker responsible for hiding and showing items.
 * @ingroup backend
 */
class Compositor {
public:
	Compositor(Scene *scene, Canvas *canvas);
	void hide(int command);
	void showAll(int command);
	void showAll(Node *node);
private:
	Canvas *canvas;
	Scene *scene;
};


#endif
