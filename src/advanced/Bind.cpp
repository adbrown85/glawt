/*
 * Bind.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Bind.hpp"


/** Initializes the @e name and @e to attributes. */
Bind::Bind(const Tag &tag) : Node(tag) {
	
	tag.get("name", name, true, false);
	tag.get("to", to, true, false);
}


/** Sets the value when the program is about to be finalized. */
/*
void Bind::onNodeEvent(NodeEvent &event) {
	
	if (event.getSource() == program) {
		index = attachment->getIndex();
		glBindFragDataLocation(program->getHandle(), index, name.c_str());
	}
}
*/


/** Finds the target, outputs, and program. */
void Bind::associate() {
	
	// Find attachment
	attachment = Attachment::find(this, to);
	if (attachment == NULL) {
		NodeException e(tag);
		e << "[Bind] Could not find attachment with name '" << to << "'.";
		throw e;
	}
	
	// Find outputs and add attachment
	outputs = Outputs::find(this);
	if (outputs == NULL) {
		NodeException e(tag);
		e << "[Outputs] Could not find outputs.";
		throw e;
	}
	index = outputs->addAttachment(attachment);
	
	// Find program
	program = Program::find(this);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Bind] Cound not find program.";
		throw e;
	}
	glBindFragDataLocation(program->getHandle(), index, name.c_str());
	
/*
	// Add listener
	program->addListener(this, NodeEvent::FINALIZE);
*/
}


/** Checks that the bind was completed successfully. */
void Bind::finalize() {
	
	GLint location;
	
	location = glGetFragDataLocation(program->getHandle(), name.c_str());
	if (location != index) {
		NodeException e(tag);
		e << "[Bind] Variable was not bound correctly.";
		throw e;
	}
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

