/*
 * Bind.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Bind.hpp"


/** Creates a new %Bind from an XML tag. */
Bind::Bind(const Tag &tag) : Node(tag) {
	
	tag.get("name", name, true, false);
	tag.get("to", to, true, false);
}


/** Finds the target and the program. */
void Bind::associate() {
	
	// Find program
	program = Program::find(this);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Bind] Cound not find program.";
		throw e;
	}
	
	// Find attachment
	attachment = Attachment::find(this, to);
	if (attachment == NULL) {
		NodeException e(tag);
		e << "[Bind] Could not find attachment with name '" << name << "'.";
		throw e;
	}
}


/** Sets the variable in the program to the location of the target. */
void Bind::finalize() {
	
	index = attachment->getIndex();
	glBindFragDataLocation(program->getHandle(), index, name.c_str());
}


/** @return String comprised of the object's attributes. */
string Bind::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << name << "'"
	       << " to='" << to << "'"
	       << " index='" << index << "'";
	return stream.str();
}

