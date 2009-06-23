/*
 * Producer.hpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PRODUCER_HEADER__
#define __PRODUCER_HEADER__
#include <cstdlib>
#include <iostream>
#include "Command.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Producer : public Delegate {
	
	
	public :
		
		Producer();
		
		virtual void run(int command);
		virtual void run(int command, float argument) {;}
	
	
	private :
		
		void cmdCopy();
		void cmdCut();
		void cmdDuplicate();
		void cmdExit();
		void cmdOpen();
		void cmdPaste();
		void cmdSave();
		
		std::map<int,void(Producer::*)()> hans;
};


#endif
