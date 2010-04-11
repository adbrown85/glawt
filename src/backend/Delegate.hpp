/*
 * Delegate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include <map>
#include <string>
#include "Command.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @interface Delegate
 * @ingroup backend
 * @brief
 *     Interface for a worker that performs %Commands on the %Scene.
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
		
		map<int,void(*)(Scene*,int)> getHandlersZero();
		map<int,void(*)(Scene*,int,float)> getHandlersFloat();
		map<int,void(*)(Scene*,int,string)> getHandlersString();
		string getType() const;
		void setScene(Scene *scene);
	
	protected :
		
		Scene *scene;
		string type;
		map<int,void(*)(Scene*,int)> handlersZero;
		map<int,void(*)(Scene*,int,float)> handlersFloat;
		map<int,void(*)(Scene*,int,string)> handlersString;
};


inline map<int,void(*)(Scene*,int)> Delegate::getHandlersZero() {
	
	return handlersZero;
}

inline map<int,void(*)(Scene*,int,float)> Delegate::getHandlersFloat() {
	
	return handlersFloat;
}


inline map<int,void(*)(Scene*,int,string)> Delegate::getHandlersString() {
	
	return handlersString;
}


inline string Delegate::getType() const {
	
	return type;
}


inline void Delegate::setScene(Scene *scene) {
	
	this->scene = scene;
}




#endif
