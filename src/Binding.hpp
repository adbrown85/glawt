/*
 * Binding.hpp
 *     Maps a combination of keys to a command.  Currently mouse bindings 
 * should not be stored with keyboard bindings.  Also only F9 or tab can be 
 * used because GLUT assigns them the same ASCII code.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __BINDING_HEADER__
#define __BINDING_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include "Command.hpp"
#define GLUT_UP_BUTTON 3
#define GLUT_DOWN_BUTTON 4
using std::map;
using std::string;



class Binding {
	
	
	private :
		
		
		bool hasArg;
		int *argi, cmd, mod, sta, trg;
		float argf;
		
		void init(int trg, int mod, int cmd, int sta);
		void init(int trg, int mod, int cmd, int sta, float arg);
		void init(int trg, int mod, int cmd, int sta, int *arg);
		
		static bool loaded;
		static map<int,string> nams;
		
		static bool isCharacter(int trigger);
		static void names() {
			nams[GLUT_KEY_LEFT] = "Left";
			nams[GLUT_KEY_RIGHT] = "Right";
			nams[GLUT_KEY_UP] = "Up";
			nams[GLUT_KEY_DOWN] = "Down";
			nams[GLUT_LEFT_BUTTON] = "LMB";
			nams[GLUT_MIDDLE_BUTTON] = "MMB";
			nams[GLUT_RIGHT_BUTTON] = "RMB";
			nams[GLUT_UP_BUTTON] = "MWU";
			nams[GLUT_DOWN_BUTTON] = "MWD";
			nams['\t'] = "Tab";
			nams[GLUT_KEY_HOME] = "Home";
			nams[GLUT_KEY_END] = "End";
			nams[GLUT_KEY_INSERT] = "Insert";
		}
	
	
	public :
		
		Binding(int trigger,
		        int modifier,
		        int command) {
			init(trigger, modifier, command, -1);
		}
		Binding(int trigger,
		        int modifier,
		        int command,
		        float argument) {
			init(trigger, modifier, command, -1, argument);
		}
		Binding(int trigger,
		        int modifier,
		        int command,
		        int state) {
			init(trigger, modifier, command, state);
		}
		Binding(int trigger,
		        int modifier,
		        int command,
		        float argument,
		        int state) {
			init(trigger, modifier, command, state, argument);
		}
		Binding(int trigger,
		        int modifier,
		        int command,
		        int *argument,
		        int state) {
			init(trigger, modifier, command, state, argument);
		}
		
		float getArgument() const;
		int getCommand() const {return cmd;}
		string getCommandStr() const {return Command::getName(cmd);}
		int getModifier() const {return mod;}
		string getModifierStr() const;
		int getState() {return sta;}
		int getTrigger() const {return trg;}
		string getTriggerStr() const;
		bool hasArgument() const {return hasArg;}
		bool hasDrag() const;
		bool hasModifier() const {return mod != 0;}
		bool isCharacter() const {return isCharacter(this->trg);}
		
		friend std::ostream& operator<<(std::ostream& stream,
                                        const Binding &b);
};


#endif
