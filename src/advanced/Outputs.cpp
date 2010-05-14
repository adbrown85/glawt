/*
 * Outputs.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Outputs.hpp"


/** Clears the @e locations array. */
Outputs::Outputs(const Tag &tag) : Applicable(tag) {
	
	locations = NULL;
	n = 0;
}


/** Deletes the @e locations array. */
Outputs::~Outputs() {
	
	if (locations != NULL) {
		delete[] locations;
	}
}


/** Adds an attachment so it will be available for output. 
 * 
 * @return Position of the attachment in the list.
 */
GLint Outputs::addAttachment(Attachment *attachment) {
	
	list<Attachment*>::iterator it;
	
	// First check if it's already there
	it = std::find(attachments.begin(), attachments.end(), attachment);
	if (it != attachments.end()) {
		return distance(attachments.begin(), it);
	}
	
	// Otherwise add it
	attachments.push_back(attachment);
	return attachments.size() - 1;
}


/** Directs OpenGL to use the attachments of the bound output variables. */
void Outputs::apply() {
	
	glDrawBuffers(n, locations);
}


/** Makes sure there's a framebuffer.
 * 
 * @throws NodeException if no Bind children were found.
 */
void Outputs::associate() {
	
	// Find framebuffer
	framebuffer = Framebuffer::find(this);
	if (framebuffer == NULL) {
		NodeException e(tag);
		e << "[Outputs] Could not find Framebuffer.";
		throw e;
	}
	
/*
	for (it=begin(); it!=end(); ++it) {
		bind = dynamic_cast<Bind*>(*it);
		if (bind != NULL) {
			binds.push_back(bind);
		}
	}
*/
}


/** Fills the @e locations array. */
void Outputs::finalize() {
	
	int i;
	list<Attachment*>::iterator it;
	
	// Validate
	if (attachments.empty()) {
		NodeException e(tag);
		e << "[Outputs] No attachments were added.";
		throw e;
	}
	
	// Initialize array
	n = Framebuffer::getMaxDrawBuffers();
	locations = new GLenum[n];
	for (int i=0; i<n; ++i) {
		locations[i] = GL_NONE;
	}
	
	// Fill array
	for (it=attachments.begin(); it!=attachments.end(); ++it) {
		i = distance(attachments.begin(), it);
		locations[i] = (*it)->getLocation();
	}
	
	
/*
	istringstream stream(blunt);
	string token;
	
	stream >> token;
	for (int i=0; stream; ++i) {
		if (token == "none") {
			locations[i] = GL_NONE;
		} else {
			locations[i] = GL_COLOR_ATTACHMENT0 + atoi(token.c_str());
		}
		stream >> token;
	}
	for (int i=0; i<n; ++i) {
		cout << locations[i] << " ";
	}
	cout << endl;
*/
/*
	locations[0] = GL_COLOR_ATTACHMENT0 + 0;
	locations[1] = GL_COLOR_ATTACHMENT0 + 1;
	locations[2] = GL_NONE;
*/
}


/** Finds an %Outputs node above another node. */
Outputs* Outputs::find(Node *node) {
	
	Outputs *outputs;
	
	node = node->getParent();
	while (node != NULL) {
		outputs = dynamic_cast<Outputs*>(node);
		if (outputs != NULL) {
			return outputs;
		}
		node = node->getParent();
	}
	return NULL;
}



/*
string Outputs::toString(GLenum attachment) const {
	
	ostringstream stream;
	
	if (attachment == GL_NONE) {
		stream << "none";
	} else {
		stream << (attachment - GL_COLOR_ATTACHMENT0);
	}
	return stream.str();
}
*/


/** @return String comprised of the object's attributes. */
string Outputs::toString() const {
	
	int i;
	list<Attachment*>::const_iterator it;
	ostringstream stream;
	
	stream << Applicable::toString();
	stream << " locations='";
	for (it=attachments.begin(); it!=attachments.end(); ++it) {
		i = distance(attachments.begin(), it);
		stream << locations[i] - GL_COLOR_ATTACHMENT0;
		if (*it != attachments.back()) {
			stream << " ";
		}
	}
	stream << "'";
	return stream.str();
}

