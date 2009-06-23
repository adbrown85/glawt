/*
 * Delegate.hpp
 *     Interface for performing a generic operation in Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DELEGATE_HEADER__
#define __DELEGATE_HEADER__
#include "Command.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Delegate {
	
	
	public :
		
		virtual void run(int command) = 0;
		virtual void run(int command, float argument) = 0;
		
		virtual std::vector<int> getCommands() {return cmds;}
		virtual std::string getType() {return type;}
		
		void setScene(Scene *scene) {this->scene = scene;}
	
	
	protected :
		
		Scene *scene;
		std::string type;
		std::vector<int> cmds;
};


#endif
