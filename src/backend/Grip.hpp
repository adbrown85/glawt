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
#include <typeinfo>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Node.hpp"
#include "Selectable.hpp"
#include "Selection.hpp"
#include "Scene.hpp"
#include "Translation.hpp"
#include "Vector.hpp"



/**
 * @brief
 *     %Delegate responsible for moving individual items around the scene.
 * @ingroup backend
 */
class Grip : public Delegate {
	
	
	public :
		
		Grip();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static Translation* findTranslation(Node *node);
		static void rotate(Scene *scene,
		                   int cmd,
		                   float argument);
		static void scale(Scene *scene,
		                  int cmd,
		                  float argument);
		static void translate(Scene *scene,
		                      int cmd,
		                      float argument);
};


#endif
