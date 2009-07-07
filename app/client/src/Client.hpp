/*
 * Client.hpp
 *     Client for visualizing volumes.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__
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
 * @defgroup client Client
 * @defgroup frontend Frontend
 * @defgroup backend Backend
 * @defgroup graph Graph
 * @defgroup data Data
 */
/**
 * @brief
 *     Ties together a %Display with %Mouse, %Keyboard, and %Menu controls.
 * @ingroup client
 */
class Client {
	
	
	public :
		
		
		Client();
		~Client();
		
		void parse(int argc, char *argv[]);
		void print();
		void start();
		
		string getName() {return name;}
		void setName(string filename);
	
	
	private :
		
		Scene *scene;
		string name, sceneFilename;
};


#endif
