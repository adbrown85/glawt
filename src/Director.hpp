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
		virtual void run(int command, float argument);
	
	
	private :
		
		void cmdGrab(int cmd, float id);
		void cmdIterate(int cmd);
		void cmdSelect(int cmd);
		
		std::map<int,void(Director::*)(int)> hans0;
		std::map<int,void(Director::*)(int,float)> hans1;
};


#endif
