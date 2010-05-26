/*
 * Log.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LOG_HPP
#define LOG_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>                      // For floats
#include <list>                         // Storing lines
#include <sstream>                      // Storing text
using namespace std;


/* Type definitions */
typedef basic_ostream< char,char_traits<char> > char_ostream_t;
typedef char_ostream_t& (*manip_func_t)(char_ostream_t&);


/** @brief Utility for logging messages.
 * @ingroup data
 * @warning Assumes messages don't include newline character.
 */
class Log {
public:
	typedef list<string>::iterator iterator;
public:
	iterator begin();
	iterator end();
	Log& operator<<(const string& text);
	Log& operator<<(int number);
	Log& operator<<(double number);
	Log& operator<<(manip_func_t manip);
private:
	list<string> lines;
	ostringstream buff;
};
inline Log::iterator Log::begin() {return lines.begin();}
inline Log::iterator Log::end() {return lines.end();}
namespace System {
	extern Log log;
}

#endif
