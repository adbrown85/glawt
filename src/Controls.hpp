/*
 * Controls.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __CONTROLS_HPP__
#define __CONTROLS_HPP__
#define CONTROLS_ROTATE_SPEED 5.0
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Scene.hpp"



class Controls {
	
	
	public :
		
		static void install(Scene *scene);
		// static void keyboard();
		static void mouse(int button, int state, int x, int y);
		static void rotate(int state, int x, int y);
		static void special(int key, int x, int y);
		static void drag(int x, int y);
	
	
	private :
		
		static bool allowRotate;
		static Scene *scene;
		static Vector last;
};


#endif
