/*
 * Producer.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
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
#include "Delegate.hpp"
#include "Factory.hpp"
#include "Parser.hpp"
#include "Scene.hpp"
#include "Tag.hpp"
using namespace std;



/**
 * @brief
 *     %Delegate responsible for creating and storing scenes.
 * @ingroup backend
 */
class Producer : public Delegate {
	
	
	public :
		
		Producer();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static void copy(Scene *scene, int command);
		static void cut(Scene *scene, int command);
		static void duplicate(Scene *scene, int command);
		static void open(Scene *scene, int command, string filename);
		static void paste(Scene *scene, int command);
		static void quit(Scene *scene, int command);
		static void save(Scene *scene, int command);
};


#endif
