/*
 * Director.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef _DIRECTOR_HPP_
#define _DIRECTOR_HPP_
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"



/**
 * @brief
 *     %Delegate responsible for selecting items in the scene.
 * @ingroup backend
 */
class Director : public Delegate {
	
	
	public :
		
		Director();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static void grab(Scene *scene, int cmd, float id);
		static void iterate(Scene *scene, int cmd);
		static void select(Scene *scene, int cmd);
};


#endif
