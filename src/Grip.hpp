/*
 * Grip.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __GRIP_HEADER__
#define __GRIP_HEADER__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Grip : public Delegate {
	
	
	public :
		
		Grip();
		
		virtual void run(int command);
		virtual void run(int command, float argument) {;}
		virtual void run(int command, float arg1, float arg2) {;}
	
	
	private :
		
		void cmdRotate(int cmd);
		void cmdScale(int cmd);
		void cmdTranslate(int cmd);
		
		std::map<int,void(Grip::*)(int)> hans;
};


#endif
