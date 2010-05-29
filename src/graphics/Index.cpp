/*
 * Index.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Index.hpp"


ostream& operator<<(ostream &stream, const Index &index) {
	
	stream << '(' << index.i
	       << ',' << index.j
	       << ',' << index.k
	       << ')';
	return stream;
}

