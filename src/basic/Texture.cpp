/*
 * Texture.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture.hpp"
vector<GLenum> Texture::active_units;


/** Creates a new texture from an XML tag.
 * 
 * @param [in] type 1D, 2D, or 3D.
 * @param [in] tag XML tag with "type", "name", and "filename" attributes.
 */
Texture::Texture(GLenum type, const Tag &tag) : Applicable(tag) {
	
	// Initialize
	this->unit = 0;
	this->handle = 0;
	this->type = type;
	tag.get("file", filename, false, false);
	tag.get("name", name, false, false);
}


/** Applies the texture. */
void Texture::apply() {
	
	// Enable texturing on unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(type);
	glBindTexture(type, handle);
	active_units.push_back(type);
}


/** Finds out which texture unit to use by looking for texture ancestors. */
void Texture::associate() {
	
	Node *current;
	Texture *texture=NULL;
	
	// Find the closest Texture ancestor
	current = this->parent;
	while (current != NULL) {
		texture = dynamic_cast<Texture*>(current);
		if (texture != NULL)
			break;
		current = current->getParent();
	}
	
	// Change unit
	if (texture != NULL)
		unit = texture->getUnit() + 1;
}


/** Temporarily disables texturing on all active units. */
void Texture::pause() {
	
	int count;
	
	// Disable each unit
	count = active_units.size();
	for (int i=0; i<count; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glDisable(active_units[i]);
	}
}


/** Removes the texture. */
void Texture::remove() {
	
	// Disable texturing on unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glDisable(type);
	active_units.pop_back();
}


/** Renables texturing on all active units. */
void Texture::restart() {
	
	int count;
	
	// Enable each unit
	count = active_units.size();
	for (int i=0; i<count; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glEnable(active_units[i]);
	}
}


/** Forms a string using the Texture's attributes. */
string Texture::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << name << "'"
	       << " unit='" << unit << "'"
	       << " handle='" << handle << "'"
	       << " file='" << filename << "'";
	return stream.str();
}

