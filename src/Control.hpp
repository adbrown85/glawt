/*
 * Control.hpp
 *     Interface for a display control.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __CONTROL_HEADER__
#define __CONTROL_HEADER__
#include <cstdlib>
#include <iostream>
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Control {
	
	
	protected :
		
		Delegate *del;
		Scene *scene;
		State *state;
	
	
	public :
		
		void initialize(Scene *scene,
		                State *state,
		                Delegate *delegate) {
			this->scene = scene;
			this->state = state;
			this->del = delegate;
		}
		virtual void install() = 0;
};


#endif
