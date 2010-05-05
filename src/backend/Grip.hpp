/*
 * Grip.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GRIP_HPP
#define GRIP_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Node.hpp"
#include "Selectable.hpp"
#include "Selection.hpp"
#include "Scene.hpp"
#include "Translation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief %Delegate responsible for moving individual items around the scene.
 */
class Grip : public Delegate {
public :
	Grip();
	static Translation* findTranslation(Node *node);
	static void rotate(Scene *scene, int cmd, float argument);
	static void scale(Scene *scene, int cmd, float argument);
	static void translate(Scene *scene, int cmd, float argument);
};


#endif
