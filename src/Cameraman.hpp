/*
 * Cameraman.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __CAMERAMAN_HEADER__
#define __CAMERAMAN_HEADER__
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using std::map;



/**
 * @brief
 *     Delegate responsible for moving or rotating the camera.
 */
class Cameraman : public Delegate {
	
	
	public :
		
		Cameraman();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
	
		static void fit(Scene *scene, int command);
		static void reset(Scene *scene, int command);
		static void rotate(Scene *scene, int command, float amount);
		static void translate(Scene *scene, int command, float amount);
};


#endif
