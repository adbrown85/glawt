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
#include <map>
#include <string>
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"
using std::multimap;
using std::string;



class Control {
	
	
	protected :
		
		Delegate *del;
		multimap<int,Binding> bins;
		Scene *scene;
		State *state;
		string className;
	
	
	public :
		
		void add(const Binding &bin) {
			bins.insert(pair<int,Binding>(bin.getTrigger(), bin));
		}
		void initialize(Scene *scene,
		                State *state,
		                Delegate *delegate) {
			this->scene = scene;
			this->state = state;
			this->del = delegate;
		}
		virtual void install() = 0;
		void print() {
			std::multimap<int,Binding>::iterator bi;
			std::cout << className << " Controls:" << std::endl;
			for (bi=bins.begin(); bi!=bins.end(); bi++)
				std::cout << "  " << bi->second << std::endl;
		}
};


#endif
