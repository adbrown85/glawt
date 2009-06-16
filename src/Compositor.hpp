/*
 * Compositor.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __COMPOSITOR_HEADER__
#define __COMPOSITOR_HEADER__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Compositor : public Delegate {
	
	
	public :
		
		Compositor();
		
		virtual void run(int command);
		virtual void run(int command, float argument) {;}
		virtual void run(int command, float arg1, float arg2) {;}
	
	
	private :
		
		void cmdHide();
		void cmdInfo();
		void cmdShowAll();
		
		std::map<int,void(Compositor::*)()> hans;
};


#endif
