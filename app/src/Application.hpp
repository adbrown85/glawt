/*
 * Application.hpp
 *     Application for visualizing volumes.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __APPLICATION_HEADER__
#define __APPLICATION_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include "Display.hpp"
#include "Interpreter.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
using std::cerr;
using std::endl;
using std::string;


/**
 * @mainpage
 * <table align="center" border="0" width="70%">
 * <tr>
 *     <td><img src="gander.png"></td>
 * </tr>
 * <tr>
 *     <td><p>Take a gander with Gander!  Gander is a scene renderer 
 *         focusing on volume rendering.  It is currently being developed by 
 *         Andy Brown as part of his Computer Science Master's project at the 
 *         Rochester Institute of Technology.
 *         <p>This document describes the C++ classes that make up Gander.  We 
 *         suggest starting with the <i>Class List</i>, which gives brief 
 *         descriptions of all the classes in one spot.  After that, check out 
 *         the <i>Class Hierarchy</i> to get a better idea of how the classes 
 *         work together.  Finally, go ahead and dive in to the actual classes 
 *         themselves.
 *         <p>For source code, check out the <a 
 *         href="http://www.sourceforge.net/projects/gander/develop"
 *         target="_parent">SourceForge project page</a>.  To see the latest 
 *         updates, see the <a 
 *         href="http://sourceforge.net/apps/wordpress/gander" 
 *         target="_parent">Gander blog</a>.
 * </td>
 * </tr>
 * </table>
 */
/**
 * @defgroup application Application
 * @defgroup backend Backend
 * @defgroup core Core
 * @defgroup frontend Frontend
 */
/**
 * @brief
 *     Ties together a %Display with %Mouse, %Keyboard, and %Menu controls.
 * @ingroup application
 */
class Application {
	
	
	public :
		
		Application();
		~Application();
		
		void parse(int argc,
		           char *argv[]);
		void print();
		void start();
	
	
	private :
		
		Scene *scene;
		string sceneFilename;
};


#endif
