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
#include "Delegate.hpp"
#include "Drawable.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Selection.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief
 *     %Delegate responsible for altering the image, including hiding %Items.
 */
class Compositor : public Delegate {
	
	public :
		
		Compositor();
		
		virtual void run(int command) {}
		virtual void run(int command, float argument) {}
		virtual void run(int command, string argument) {}
		
		static void hide(Scene *scene, int command);
		static void info(Scene *scene, int command);
		static void showAll(Scene *scene, int command);
		static void showAll(Node *node);
};


#endif
