/*
 * Client.hpp
 *     Client for visualizing volumes.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include "DatasetHeader.hpp"
#include "Display.hpp"
#include "Interpreter.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"
#include "Preprocessor.hpp"
#include "Scene.hpp"
#include "VlbMaker.hpp"
using namespace std;


/**
 * @mainpage
 * @image html gander.png
 * 
 * <table align="center" border="0" style="width:34em"><tr><td>
 * This document describes the C++ classes that make up Gander.  We suggest 
 * starting with the @e Modules page, which gives a good overview of how the 
 * application is divided up into several different layers, starting at the 
 * bottom with @e Data and moving all the way up to @e Graph, @e Backend, 
 * @e Frontend, and finally @e %Client.</p>
 * 
 * After that, check out the <i>Class Hierarchy</i> to get a better idea of 
 * how the classes work together, or go ahead and dive in to the actual 
 * classes themselves.
 * 
 * For the latest source code, check out our <a href="http://gander.git.sf.net" 
 * target="_blank">Git repository</a>.
 * </td></tr></table>
 * 
 * @defgroup client Client
 * @defgroup frontend Frontend
 * @defgroup backend Backend
 * @defgroup graph Graph
 * @defgroup traits Traits
 * @defgroup data Data
 */
/**
 * @brief
 *     Ties together a %Display with %Mouse, %Keyboard, and %Menu controls.
 * @ingroup client
 */
class Client {
	
	public:
		
		void banner();
		void display();
		void onHeader();
		void onPreprocess();
		void onVlb();
		void parse(int argc,
		           char *argv[]);
		void start();
	
	private:
		
		Scene scene;
		string inFilename, option, outFilename, title;
};


#endif
