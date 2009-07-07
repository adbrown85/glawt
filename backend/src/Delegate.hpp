/*
 * Delegate.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef _DELEGATE_HPP_
#define _DELEGATE_HPP_
#include <map>
#include <string>
#include "Command.hpp"
#include "Scene.hpp"
using std::map;
using std::string;



/**
 * @brief
 *     Interface for a worker that performs Commands on the Scene.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Interpreter
 * @see Producer
 */
class Delegate {
	
	
	public :
		
		virtual void run(int command) = 0;
		virtual void run(int command, float argument) = 0;
		virtual void run(int command, string argument) = 0;
		
		map<int,void(*)(Scene*,int)> getHandlersZero() {
			return handlersZero;
		}
		map<int,void(*)(Scene*,int,float)> getHandlersFloat() {
			return handlersFloat;
		}
		map<int,void(*)(Scene*,int,string)> getHandlersString() {
			return handlersString;
		}
		virtual string getType() {return type;}
		void setScene(Scene *scene) {this->scene = scene;}
	
	
	protected :
		
		Scene *scene;
		string type;
		map<int,void(*)(Scene*,int)> handlersZero;
		map<int,void(*)(Scene*,int,float)> handlersFloat;
		map<int,void(*)(Scene*,int,string)> handlersString;
};


#endif
