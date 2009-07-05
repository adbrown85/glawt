/*
 * Grip.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __GRIP_HEADER__
#define __GRIP_HEADER__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"



/**
 * @brief
 *     Delegate responsible for moving individual items around the scene.
 */
class Grip : public Delegate {
	
	
	public :
		
		Grip();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static void rotate(Scene *scene, int cmd);
		static void scale(Scene *scene, int cmd);
		static void translate(Scene *scene, int cmd);
};


#endif
