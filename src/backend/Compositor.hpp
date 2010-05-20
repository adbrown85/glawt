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


/**
 * @ingroup backend
 * @brief %Delegate responsible for hiding and showing items.
 */
class Compositor : public Delegate {
public :
	Compositor();
	static void hide(Scene *scene, int command);
	static void showAll(Scene *scene, int command);
	static void showAll(Node *node);
};


#endif
