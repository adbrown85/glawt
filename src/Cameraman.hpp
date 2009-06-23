/*
 * Cameraman.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __CAMERAMAN_HEADER__
#define __CAMERAMAN_HEADER__
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Cameraman : public Delegate {
	
	
	public :
		
		Cameraman();
		
		virtual void run(int command);
		virtual void run(int command, float argument);
	
	
	private :
		
		void cmdFit(int cmd);
		void cmdReset(int cmd);
		void cmdRotate(int cmd, float amt);
		void cmdTrans(int cmd, float amt);
		
		std::map<int,void(Cameraman::*)(int)> hans0;
		std::map<int,void(Cameraman::*)(int,float)> hans1;
};


#endif
