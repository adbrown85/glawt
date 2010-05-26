/*
 * Log.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Log.hpp"
namespace System {
	Log log;
}


Log& Log::operator<<(manip_func_t manip) {
	
	if (manip == (manip_func_t)endl) {
		lines.push_back(buff.str());
		buff.str("");
	} else {
		(*manip)(buff);
	}
	(*manip)(cerr);
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
	
	buff << fixed << setprecision(2);
	buff << number;
	cerr << fixed << setprecision(2);
	cerr << number;
	return *this;
}

