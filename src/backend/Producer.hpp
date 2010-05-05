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
#include "Exception.hpp"
#include "AdvancedFactory.hpp"
#include "BasicFactory.hpp"
#include "Command.hpp"
#include "Delegate.hpp"
#include "Factory.hpp"
#include "Scene.hpp"
#include "Tag.hpp"
#include "Translation.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief  %Delegate responsible for creating and storing scenes.
 */
class Producer : public Delegate {
public:
	Producer();
	static void copy(Scene *scene, int command);
	static void cut(Scene *scene, int command);
	static void duplicate(Scene *scene, int command);
	static void list(Scene *scene, int command);
	static void open(Scene *scene, int command, string filename);
	static void paste(Scene *scene, int command);
	static void quit(Scene *scene, int command);
	static void save(Scene *scene, int command);
};


#endif
