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


/** Adds attachment to outputs and sets its index in outputs to program value.
 * 
 * @throws NodeException if maximum number of outputs exceeded.
 */
void Bind::associate() {
	
	// Find required nodes
	findAttachment();
	findOutputs();
	findProgram();
	
	// Add attachment
	index = outputs->addAttachment(attachment);
	if (index == -1) {
		NodeException e(tag);
		e << "[Bind] Maximum number of outputs exceeded.";
		throw e;
	}
	
	// Set location
	glBindFragDataLocationGAN(program->getHandle(), index, name.c_str());
}


/** Checks that the variable's value was set successfully.
 * 
 * @throws NodeException if the value in the program does not match.
 */
void Bind::finalize() {
	
	GLint location;
	
	location = glGetFragDataLocationGAN(program->getHandle(), name.c_str());
	if (location != index) {
		NodeException e(tag);
		e << "[Bind] Variable was not bound correctly.";
		throw e;
	}
}


/** @throws NodeException if Attachment named @e to could not be found. */
void Bind::findAttachment() {
	
	attachment = Attachment::find(this, to);
	if (attachment == NULL) {
		NodeException e(tag);
		e << "[Bind] Could not find attachment with name '" << to << "'.";
		throw e;
	}
}


/** @throws NodeException if could not find Outputs list. */
void Bind::findOutputs() {
	
	outputs = Outputs::find(this);
	if (outputs == NULL) {
		NodeException e(tag);
		e << "[Bind] Could not find outputs.";
		throw e;
	}
}


/** @throws NodeException if could not find Program. */
void Bind::findProgram() {
	
	program = Program::find(this);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Bind] Could not find program.";
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

