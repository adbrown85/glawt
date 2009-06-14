/*
 * Delegate.hpp
 *     Interface for performing a generic operation in Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __GANDER_DELEGATE_HEADER__
#define __GANDER_DELEGATE_HEADER__
#include "Command.hpp"



class Delegate {
	
	
	public :
		
		virtual void run(int command) = 0;
};


#endif
