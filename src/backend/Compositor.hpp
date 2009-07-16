/*
 * Compositor.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __COMPOSITOR_HPP__
#define __COMPOSITOR_HPP__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"



/**
 * @brief
 *     %Delegate responsible for altering the image, including hiding %Items.
 * @ingroup backend
 */
class Compositor : public Delegate {
	
	
	public :
		
		Compositor();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static void hide(Scene *scene, int command);
		static void info(Scene *scene, int command);
		static void showAll(Scene *scene, int command);
};


#endif
