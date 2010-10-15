/*
 * Log.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Log.hpp"
Log glog;


Log::Log() {
	
	buff << fixed << setprecision(2);
}


void Log::addListener(LogListener *listener) {
	
	listeners.push_back(listener);
}


void Log::fireUpdate(const string &text) {
	
	list<LogListener*>::iterator it;
	
	for (it=listeners.begin(); it!=listeners.end(); ++it) {
		(*it)->onLogUpdate(text);
	}
}


Log& Log::operator<<(manip_func_t manip) {
	
	(*manip)(cerr);
	if (manip == (manip_func_t)endl) {
		lines.push_back(buff.str());
		fireUpdate(buff.str());
		buff.str("");
	} else {
		(*manip)(buff);
	}
	return *this;
}


Log& Log::operator<<(const string &text) {
	
	buff << text;
	cerr << text;
	return *this;
}


Log& Log::operator<<(int number) {
	
	buff << number;
	cerr << number;
	return *this;
}


Log& Log::operator<<(double number) {
	
	buff << number;
	cerr << number;
	return *this;
}

