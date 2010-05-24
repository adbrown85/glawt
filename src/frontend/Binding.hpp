/*
 * Binding.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BINDING_HPP
#define BINDING_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include "Command.hpp"
#include "Canvas.hpp"
using namespace std;


/** Maps a combination of keys or buttons to a command.
 * @ingroup frontend
 */
class Binding {
public:
	Binding(int trigger, int modifier, int command);
	Binding(int trigger, int modifier, int command, float arg);
	Binding(int trigger, int modifier, int command, int state);
	Binding(int trigger, int modifier, int command, float arg, int state);
	Binding(int trigger, int modifier, int command, GLuint *arg, int state);
	float getArgument() const;
	int getCommand() const;
	string getCommandStr() const;
	int getModifier() const;
	string getModifierStr() const;
	int getState() const;
	int getTrigger() const;
	string getTriggerStr() const;
	bool hasArgument() const;
	bool hasDrag() const;
	bool hasModifier() const;
	bool isCharacter() const;
	friend ostream& operator<<(ostream& stream, const Binding &b);
protected:
	void init(int trigger, int modifier, int command, int state);
	void init(int trigger, int modifier, int command, int state, float arg);
	void init(int trigger, int modifier, int command, int state, GLuint *arg);
	static bool isCharacter(int trigger);
	static void initTriggerNames();
private:
	bool hasArg;
	int command, modifier, state, trigger;
	unsigned int *argi;
	float argf;
	static bool loaded;
	static map<int,string> triggerNames;
};

inline int Binding::getCommand() const {return command;}
inline string Binding::getCommandStr() const {return Command::getName(command);}
inline int Binding::getModifier() const {return modifier;}
inline int Binding::getState() const {return state;}
inline int Binding::getTrigger() const {return trigger;}
inline bool Binding::hasArgument() const {return hasArg;}
inline bool Binding::hasModifier() const {return modifier != 0;}
inline bool Binding::isCharacter() const {return isCharacter(this->trigger);}






#endif
