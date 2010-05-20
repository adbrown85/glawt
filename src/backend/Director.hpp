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
#include "Delegate.hpp"
#include "Identifiable.hpp"
#include "Node.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief %Delegate responsible for selecting items in the scene.
 */
class Director : public Delegate {
public:
	Director();
	static void grab(Scene *scene, int cmd, float id);
	static void iterate(Scene *scene, int cmd);
	static void select(Scene *scene, int cmd);
};


#endif
