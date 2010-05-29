/*
 * Exception.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Exception.hpp"


Exception::Exception(const Exception &e) {
	
	buffer << e.getMessage();
}


Exception::Exception(const string &message) {
	
	buffer << message;
}


string Exception::getMessage() const {
	
	return buffer.str();
}


ostream& Exception::operator<<(const string &message) {
	
	buffer << message;
	return buffer;
}


ostream& Exception::operator<<(const Exception &e) {
	
	buffer << e.getMessage();
	return buffer;
}


ostream& operator<<(ostream &stream,
                    Exception &e) {
	
	stream << e.buffer.str();
	return stream;
}


const char* Exception::what() const throw() {
	
	return buffer.str().c_str();
}

