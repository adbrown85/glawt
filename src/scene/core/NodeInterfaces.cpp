/*
 * NodeInterfaces.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeInterfaces.hpp"


/** Gets the name from the tag. */
Nameable::Nameable(const Tag &tag) {
	
	tag.get("name", name, false, false);
}


/** @return String with the object's name if it has one. */
string Nameable::toString() const {
	
	ostringstream stream;
	
	if (hasName())
		stream << " name='" << name << "'";
	return stream.str();
}


/** Gets the filename from the tag. */
Fileable::Fileable(const Tag &tag) {
	
	tag.get("file", filename, false, false);
}


/** @return String with the object's filename if it has one. */
string Fileable::toString() const {
	
	ostringstream stream;
	
	if (hasFilename())
		stream << " file='" << filename << "'";
	return stream.str();
}

