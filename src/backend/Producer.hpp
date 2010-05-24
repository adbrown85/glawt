/*
 * Producer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PRODUCER_HPP
#define PRODUCER_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>
#include "Command.hpp"
#include "AdvancedFactory.hpp"
#include "BasicFactory.hpp"
#include "Translate.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief  %Delegate responsible for creating and storing scenes.
 */
class Producer : public Delegate {
public:
	Producer();
	static void copy(Scene *scene, Canvas *canvas, int command);
	static void cut(Scene *scene, Canvas *canvas, int command);
	static void duplicate(Scene *scene, Canvas *canvas, int command);
	static void list(Scene *scene, Canvas *canvas, int command);
	static void open(Scene *s, Canvas *c, int command, const string &arg);
	static void paste(Scene *scene, Canvas *canvas, int command);
	static void quit(Scene *scene, Canvas *canvas, int command);
	static void save(Scene *scene, Canvas *canvas, int command);
};


#endif
