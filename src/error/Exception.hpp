/*
 * Exception.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include "common.h"
#include <exception>
using namespace std;


/** @brief %Exception backed by a stringstream for easy message building.
 * @ingroup system
 */
class Exception : public exception {
public:
	Exception() {};
	Exception(const Exception &e);
	Exception(const string &message);
	~Exception() throw() {}
	string getMessage() const;
	const char* what() const throw();
	ostream& operator<<(const string &message);
	ostream& operator<<(const Exception &e);
	friend ostream& operator<<(ostream& stream, Exception &e);
private:
	ostringstream buffer;
};


#endif
