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
#include "Traverser.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Utility for testing nodes.
 */
class Tester {
public:
	static void display(void);
	static string getFilename();
	static Scene* getScene();
	static void keyboard(unsigned char key, int x, int y);
	static void open(const string &filename);
	static void start();
private:
	static Traverser *traverser;
	static Scene scene;
};


inline Scene* Tester::getScene() {return &scene;}
inline string Tester::getFilename() {return scene.getFilename();}


#endif
