/*
 * Binding.hpp
 *     Maps a combination of keys to a command.
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
#include "Command.hpp"



class Binding {
	
	
	private :
		
		bool hasArg, hasSte, isCha;
		int trg, cmd, mod, ste;
		float arg;
		
		void init(int trigger, int command);
		
		static bool loaded;
		static std::map<int,std::string> keys;
		
		static void names() {
			keys[GLUT_KEY_LEFT] = "Left";
			keys[GLUT_KEY_RIGHT] = "Right";
			keys[GLUT_KEY_UP] = "Up";
			keys[GLUT_KEY_DOWN] = "Down";
			keys[GLUT_KEY_F1] = "F1";
			keys[GLUT_KEY_F2] = "F2";
			keys[GLUT_KEY_F3] = "F3";
			keys[GLUT_KEY_F4] = "F4";
			keys[GLUT_KEY_F5] = "F5";
			keys[GLUT_KEY_F6] = "F6";
			keys[GLUT_KEY_F7] = "F7";
			keys[GLUT_KEY_F8] = "F8";
			keys['\t'] = "Tab";
			keys[GLUT_KEY_F10] = "F10";
			keys[GLUT_KEY_F11] = "F11";
			keys[GLUT_KEY_F12] = "F12";
			keys[GLUT_KEY_HOME] = "Home";
			keys[GLUT_KEY_END] = "End";
			keys[GLUT_KEY_INSERT] = "Insert";
		}
	
	
	public :
		
		Binding(int trigger,
		        int command) {
			isCha = false;
			init(trigger, command);
		}
		Binding(int trigger,
		        int command,
		        int modifier) {
			isCha = false;
			init(trigger, command);
			mod = modifier;
		}
		Binding(int trigger,
		        int command,
		        float argument) {
			isCha = false;
			init(trigger, command);
			arg = argument;
			hasArg = true;
		}
		Binding(int trigger,
		        int command,
		        int modifier,
		        float argument) {
			isCha = false;
			init(trigger, command);
			mod = modifier;
			hasArg = true;
			arg = argument;
		}
		Binding(char key,
		        int command) {
			isCha = true;
			init(key, command);
		}
		Binding(char key,
		        int command,
		        int modifier) {
			isCha = true;
			init(key, command);
			mod = modifier;
		}
		Binding(char key,
		        int command,
		        int modifier,
		        float argument) {
			isCha = true;
			init(key, command);
			mod = modifier;
			hasArg = true;
			arg = argument;
		}
		
		float getArgument() const {return arg;}
		int getCommand() const {return cmd;}
		std::string getCommandStr() const {return Command::getName(cmd);}
		int getModifier() const {return mod;}
		std::string getModifierStr() const;
		std::string getName() const;
		char getKey() const {return static_cast<char>(trg);}
		int getTrigger() const {return trg;}
		bool hasArgument() const {return hasArg;}
		bool hasModifier() const {return mod != 0;}
		bool isChar() const {return isCha;}
		
		friend std::ostream& operator<<(std::ostream& stream,
                                        const Binding &b);
};


#endif
