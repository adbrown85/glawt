/*
 * Worker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WORKER_HPP
#define WORKER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Scene.hpp"
#include "Canvas.hpp"
using namespace std;


class Worker {
public:
	Worker(Scene *scene, Canvas *canvas);
protected:
	Scene *scene;
	Canvas *canvas;
};


#endif
