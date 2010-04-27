/*
 * Display.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Command.hpp"             // Open the scene
#include "Control.hpp"             // Install controls before starting
#include "Interpreter.hpp"         // Send commands
#include "Manipulator.hpp"         // Draw UI widgets for controls
#include "Scene.hpp"               // Pass root node to Painter
#include "Painter.hpp"             // Paints the screen with scene
#include "RenderFactory.hpp"
#include "ShapeFactory.hpp"
#include "ShaderFactory.hpp"
#include "TextureFactory.hpp"
#include "TransformFactory.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     3D display for items in a scene.
 */
class Display {
	
	public :
		
		static void display(void);
		static void idle(void);
		static void install(Control *control);
		static void start(int argc,
		                  char *argv[],
		                  string title,
		                  Scene *scene,
		                  Interpreter *interpreter);
		static void toggleOverlay();
	
	private :
		
		static bool useOverlay;
		static Interpreter *interpreter;
		static unsigned long timeStarted;
		static int frames, framesPerSecond;
		static Scene *scene;
		static vector<Control*> controls;
		static vector<Manipulator*> manipulators;
		
		static void overlay();
		static void checkError();
};


#endif
