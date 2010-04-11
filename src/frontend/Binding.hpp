/*
 * Binding.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BINDING_HPP
#define BINDING_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include "Command.hpp"
#define GLUT_UP_BUTTON 3
#define GLUT_DOWN_BUTTON 4
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Maps a combination of keys or buttons to a command.
 * 
 * @bug Currently mouse bindings should not be stored with keyboard bindings.
 * @bug F9 and Tab should not both be used because GLUT codes are the same.
 */
class Binding {
	
	public :
		
		Binding(int trigger,
		        int modifier,
		        int command);
		Binding(int trigger,
		        int modifier,
		        int command,
		        float argument);
		Binding(int trigger,
		        int modifier,
		        int command,
		        int state);
		Binding(int trigger,
		        int modifier,
		        int command,
		        float argument,
		        int state);
		Binding(int trigger,
		        int modifier,
		        int command,
		        unsigned int *argument,
		        int state);
		float getArgument() const;
		int getCommand() const {return command;}
		string getCommandStr() const {return Command::getName(command);}
		int getModifier() const {return modifier;}
		string getModifierStr() const;
		int getState() {return state;}
		int getTrigger() const {return trigger;}
		string getTriggerStr() const;
		bool hasArgument() const {return hasArg;}
		bool hasDrag() const;
		bool hasModifier() const {return modifier != 0;}
		bool isCharacter() const {return isCharacter(this->trigger);}
		
		friend ostream& operator<<(ostream& stream,
		                           const Binding &b);
	
	private :
		
		bool hasArg;
		int command, modifier, state, trigger;
		unsigned int *argi;
		float argf;
		
		void init(int trigger,
		          int modifier,
		          int command,
		          int state);
		void init(int trigger,
		          int modifier,
		          int command,
		          int state,
		          float arg);
		void init(int trigger,
		          int modifier,
		          int command,
		          int state,
		          unsigned int *arg);
		
		static bool loaded;
		static map<int,string> triggerNames;
		
		static bool isCharacter(int trigger);
		static void initTriggerNames();
};


#endif
