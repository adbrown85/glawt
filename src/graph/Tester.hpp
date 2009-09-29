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
#include "Scene.hpp"
#include "Node.hpp"
using namespace std;



class Tester {
	
	
	public :
		
		static Scene scene;
		
		static void display(void);
		static void initialize(string title);
		static void keyboard(unsigned char key,
		                     int x,
		                     int y);
		static void open(string filename);
		static void traverse(Node *node);
		static void traverseChildren(Node *node);
		static void start();
};


#endif
