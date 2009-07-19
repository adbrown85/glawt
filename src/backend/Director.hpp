/*
 * Director.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DIRECTOR_HPP__
#define __DIRECTOR_HPP__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Identifiable.hpp"
#include "Scene.hpp"
#include "Shape.hpp"
#include "Selectable.hpp"
#include "Selection.hpp"



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
