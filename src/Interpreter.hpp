/*
 * Interpreter.hpp
 *     Interprets commands and relegates them to delegates.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __INTERPRETER_HEADER__
#define __INTERPRETER_HEADER__
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
#include "State.hpp"
using std::map;
using std::vector;



class Interpreter : public Delegate {
	
	
	public :
		
		Interpreter(Scene *scene);
		~Interpreter();
		
		void print();
		virtual void run(int command);
		virtual void run(int command, float argument);
	
	
	private:
		
		Interpreter();
		
		map<int, Delegate*> hans;
		vector<Delegate*> dels;
		
		void load() {
			dels.push_back(new Cameraman());
			dels.push_back(new Compositor());
			dels.push_back(new Director());
			dels.push_back(new Grip());
			dels.push_back(new Producer());
		}
};


#endif
