/*
 * gander.hxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GANDER_HXX
#define GANDER_HXX
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Display.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Inspector.hpp"
#include "LogBook.hpp"
#include "DatasetAnalyzer.hpp"
#include "DatasetHeader.hpp"
#include "DatasetViewer.hpp"
#include "DatasetWriter.hpp"
#include "Preprocessor.hpp"
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
 * @e Frontend, and finally @e %gander.</p>
 * 
 * After that, check out the <i>Class Hierarchy</i> to get a better idea of 
 * how the classes work together, or go ahead and dive in to the actual 
 * classes themselves.
 * 
 * For the latest source code, check out our <a href="http://gander.git.sf.net" 
 * target="_blank">Git repository</a>.
 * </td></tr></table>
 * 
 * @defgroup data Data
 * @defgroup graph Graph
 * @defgroup basic Basic
 * @defgroup advanced Advanced
 * @defgroup backend Backend
 * @defgroup frontend Frontend
 */
/**
 * @brief Main application.
 */
class Gander {
public:
	Gander(int argc, char *argv[]);
	~Gander();
	void start();
protected:
	void banner();
	void onCompile();
	void onConvert();
	void onDisplay();
	void onHeader();
	void onHistogram();
	void onPreprocess();
	void onRange();
	void onSlices();
	void parse();
	void usage();
private:
	int argc;
	char **argv;
	Display *display;
	Delegate *delegate;
	Canvas *canvas;
	Scene *scene;
	string inFilename, option, outFilename, parameter, title;
};


#endif
