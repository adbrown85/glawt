/*
 * Display.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DISPLAY_HEADER__
#define __DISPLAY_HEADER__
#define DISPLAY_DEFAULT_X 100
#define DISPLAY_DEFAULT_Y 100
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Control.hpp"
#include "Item.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "Outline.hpp"
#include "Quaternion.hpp"
#include "Scene.hpp"
#include "Manipulator.hpp"
#include "Translation.hpp"
#include "Vector.hpp"
using std::vector;



/**
 * @brief
 *     3D display for items in a scene.
 * @ingroup frontend
 */
class Display {
	
	
	public :
		
		static void display(void);
		static void draw(Node *node);
		static void drawChildren(Node *node);
		static void install(Control *control);
		static void start(std::string title, Scene *scene);
	
	
	private :
		
		static Outline outline;
		static Scene *scene;
		static vector<Control*> controls;
		static vector<Manipulator*> manipulators;
		
		static void overlay();
};


#endif
