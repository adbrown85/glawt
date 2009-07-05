/*
 * Producer.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PRODUCER_HEADER__
#define __PRODUCER_HEADER__
#include <cstdlib>
#include <iostream>
#include <string>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using std::string;



/**
 * @brief
 *     Delegate responsible for creating and storing scenes.
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
