/*
 * Worker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WORKER_HPP
#define WORKER_HPP
#include "common.h"
#include "Command.hpp"
using namespace std;


/** @brief Base class for an object that performs commands on the scene.
 * @ingroup command
 */
class Worker {
public:
	Worker(Scene *scene, Canvas *canvas);
protected:
	Scene *scene;
	Canvas *canvas;
};


#endif
