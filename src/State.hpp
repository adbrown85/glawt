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
#include "Item.hpp"
#include "Vector.hpp"



class State {
	
	
	public :
		
		ItemPtrSet selection;
		Vector currMouse, prevMouse;
};


#endif
