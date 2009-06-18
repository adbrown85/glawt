/*
 * State.hpp
 *     Holds shared information for the application.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __STATE_HEADER__
#define __STATE_HEADER__
#include <cstdlib>
#include <iostream>
#include <set>
#include "Item.hpp"
#include "Vector.hpp"
using std::set;



class State {
	
	
	public :
		
		bool manAct;
		Vector manVec;
		
		State() {
			manAct = false;
		}
		
		void setManipulator(bool state) {
			manAct = state;
			std::cout << "Manipulator is " << manAct << std::endl;
		}
};


#endif
