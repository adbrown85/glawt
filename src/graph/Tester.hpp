/*
 * Tester.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TESTER_HPP
#define TESTER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Applicable.hpp"
#include "Drawable.hpp"
#include "FileUtility.hpp"
#include "Node.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * Creator function.
 */
typedef void (*callback_t)(void);


class Tester {
	
	public :
		
		static map<string,callback_t> callbacks;
		static Scene scene;
		
		static void display(void);
		static callback_t findCallback(const string &name);
		static Scene* getScene();
		static void init(int argc,
		                 char *argv[]);
		static void keyboard(unsigned char key,
		                     int x,
		                     int y);
		static void open(const string &filename);
		static void setCallback(const string &name,
		                        callback_t callback);
		static void traverse(Node *node);
		static void traverseChildren(Node *node);
		static void start();
};


#endif
