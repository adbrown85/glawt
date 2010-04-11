/*
 * Interpreter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Cameraman.hpp"
#include "Command.hpp"
#include "Compositor.hpp"
#include "Delegate.hpp"
#include "Director.hpp"
#include "Grip.hpp"
#include "Producer.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief
 *     Interprets commands and passes them on to other %Delegates.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Producer
 */
class Interpreter : public Delegate {
	
	public :
		
		Interpreter(Scene *scene);
		~Interpreter();
		
		void print();
		virtual void run(int command);
		virtual void run(int command, float argument);
		virtual void run(int command, string argument);
	
	private:
		
		Interpreter();
		
		vector<Delegate*> delegates;
};


#endif
