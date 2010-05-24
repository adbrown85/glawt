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
#include "Node.hpp"
#include "FileUtility.hpp"
#include "Scene.hpp"
#include "Traverser.hpp"
#include "Canvas.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Utility for testing nodes.
 */
class Tester {
public:
	static void display(void);
	static string getFilename();
	static Scene* getScene();
	static void keyboard(int key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void init(int argc, char *argv[]);
	static void open(const string &filename);
	static void start();
private:
	static Traverser *traverser;
	static Scene scene;
	static Canvas *canvas;
};


inline Scene* Tester::getScene() {return &scene;}
inline string Tester::getFilename() {return scene.getFilename();}


#endif
