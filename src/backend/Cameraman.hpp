/*
 * Cameraman.hpp
 *     Responsible for moving the camera.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef CAMERAMAN_HPP
#define CAMERAMAN_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using namespace std;



/**
 * @brief
 *     %Delegate responsible for moving or rotating the camera.
 * @ingroup backend
 */
class Cameraman : public Delegate {
	
	
	public :
		
		Cameraman();
		
		virtual void run(int command) {}
		virtual void run(int command,
		                 float argument) {}
		virtual void run(int command,
		                 string argument) {}
	
		static void fit(Scene *scene,
		                int command);
		static void reset(Scene *scene,
		                  int command);
		static void rotate(Scene *scene,
		                   int command,
		                   float amount);
		static void translate(Scene *scene,
		                      int command,
		                      float amount);
};


#endif

