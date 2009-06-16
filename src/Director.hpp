/*
 * Director.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DIRECTOR_HEADER__
#define __DIRECTOR_HEADER__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Director : public Delegate {
	
	
	public :
		
		Director();
		
		virtual void run(int command);
		virtual void run(int command, float argument) {;}
		virtual void run(int command, float arg1, float arg2);
	
	
	private :
		
		void cmdGrab(int cmd, float x, float y);
		void cmdIterate(int cmd);
		void cmdSelect(int cmd);
		
		std::map<int,void(Director::*)(int)> hans0;
		std::map<int,void(Director::*)(int,float,float)> hans2;
};


#endif
